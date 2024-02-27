/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:30:33 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/27 16:41:00 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_map_line(t_list **map_list, char *line)
{
	t_list	*node;

	node = ft_lstnew(ft_strdup(line));
	if (!node)
		return ; //malloc error
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

int	get_map_height(t_list *map_list)
{
	// int	height;

	// height = 0;
	// while (map_list)
	// {
	// 	height++;
	// 	map_list = map_list->next;
	// }
	// return (height);
	return (ft_lstsize(map_list));
}

static int	char_to_int(char c) //change this later
{
	int	tile;
	
	tile = -1;
	if (c == '0')
		tile = 0;
	if (c == '1')
		tile = 1;
	if (c == 'N')
		tile = 2;
	if (c == 'S')
		tile = 3;
	if (c == 'E')
		tile = 4;
	if (c == 'O')
		tile = 5;
	if (c == 'D')
		tile = 6;
	return  (tile);
}

int	**get_2d_map(t_list *map_list, int height, int width)
{
	int	**map;
	int	i;
	int	row;
	int	col;
	char	*line;

	map = malloc(sizeof(int *) * height);
	i = 0;
	while (i < height)
	{
		map[i] = malloc(sizeof(int) * width);
		ft_memset(map[i], 0, sizeof(int) * width); //or something else ?
		i++;
	}
	row = 0;
	while (map_list)
	{
		line = (char *)map_list->content;
		col = 0;
		while (line[col] && col < width)
		{
			map[row][col] = char_to_int(line[col]);
			col++;
		}
		row++;
		map_list = map_list->next;
	}
	return (map);
}

