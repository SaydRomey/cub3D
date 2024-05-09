/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:34:21 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/09 18:33:21 by cdumais          ###   ########.fr       */
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

/* **this version removes trailing whitespaces after last 'wall' char
*/
// void	store_map_line(t_list **map_list, char *line)
// {
// 	t_list	*node;
// 	char	*copy;
// 	char	*last_one;
// 	char	*trimmed;
// 	size_t	new_len;

// 	copy = ft_strdup(line);
// 	if (!copy)
// 		return ; //malloc error
// 	last_one = ft_strrchr(copy, '1');
// 	if (last_one != NULL)
// 	{
// 		new_len = last_one - copy + 1;
// 		trimmed = ft_substr(copy, 0, new_len);
// 		if (!trimmed)
// 		{
// 			free(copy);
// 			return ; //malloc error
// 		}
// 		free(copy);
// 	}
// 	else
// 		trimmed = copy;
// 	node = ft_lstnew(trimmed);
// 	if (!node)
// 	{
// 		free(copy);
// 		return ; //malloc error
// 	}
// 	ft_lstadd_back(map_list, node);
// }
