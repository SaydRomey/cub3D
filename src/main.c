/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:35:04 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/29 21:57:25 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list	**call_mem_list(void)
{
	static t_list	*mem_list = NULL; // Initialize to NULL

	return (&mem_list); // Return the address of the static variable
}

void	*track_calloc(size_t count, size_t size)
{
	void	*ptr;
	t_list	**mem_list_ptr;
	t_list	*new_node;

	ptr = ft_calloc(count, size);
	mem_list_ptr = call_mem_list(); // Get the address of the static list
	if (ptr)
	{
		new_node = ft_lstnew(ptr);
		if (new_node)
			ft_lstadd_front(mem_list_ptr, new_node); // Modify the original list
		else
			return (free(ptr), NULL); // If we can't track it, don't allocate it
	}
	return (ptr);
}
