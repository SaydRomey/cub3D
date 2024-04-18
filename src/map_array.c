/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:30:33 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/18 18:20:28 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_row(int *grid, int width, int value)
{
	int	j;

	j = 0;
	while (j < width)
	{
		grid[j] = value;
		j++;
	}
}

/*
check with ft_calloc instead, if filling it is necessary..

*/
int	**allocate_grid(int height, int width)
{
	int	**grid;
	int	i;

	grid = (int **)malloc(sizeof(int *) * height);
	if (!grid)
		return (NULL);
	i = 0;
	while (i < height)
	{
		grid[i] = (int *)malloc(sizeof(int) * width);
		if (!grid[i])
		{
			while (--i >= 0)
				free(grid[i]);
			free(grid);
			return (NULL);
		}
		fill_row(grid[i], width, -2);
		i++;
	}
	return (grid);
}

static int	char_to_int(char c)
{
	if (c == ' ')
		return (-1);
	else if (c == '1')
		return (1);
	else if (c == '0')
		return (0);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	else if (c == '2')
		return (2);
	else if (c == '3')
		return (3);
	else
		return (-2);
}

int	**get_2d_map(t_list *map_list, int height, int width)
{
	int		**map_array;
	int		row;
	int		col;
	char	*line;

	map_array = allocate_grid(height, width);
	if (!map_array)
		return (NULL);
	row = 0;
	while (map_list)
	{
		line = (char *)map_list->content;
		col = 0;
		while (col < width && line[col])
		{
			map_array[row][col] = char_to_int(line[col]);
			col++;
		}
		map_list = map_list->next;
		row++;
	}
	return (map_array);
}
