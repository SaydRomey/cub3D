/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:01:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/04 16:54:02 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_info	*call_info(void)
{
	static t_info	*info;

	if (info == NULL)
	{
		info = ft_calloc(1, sizeof(*info));
		if (!info)
			return (NULL);
	}
	return (info);
}

void	free_info(void)
{
	t_info	*info;
	
	info = call_info();
	// 
	free(info);
}

bool	there_is_a_problem(void)
{
	return (call_info()->problem);
}