/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:34:21 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/06 17:28:26 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_map_line(t_list **map_list, char *line)
{
	t_list	*node;

	node = ft_lstnew(ft_strtrim(line, "\n"));
	if (!node)
		return ;
	ft_lstadd_back(map_list, node);
}

int	get_map_width(t_list *map_list)
{
	int	max_width;
	int	current_length;

	max_width = 0;
	while (map_list)
	{
		current_length = ft_strlen((char *)map_list->content);
		if (current_length > max_width)
			max_width = current_length;
		map_list = map_list->next;
	}
	return (max_width);
}
