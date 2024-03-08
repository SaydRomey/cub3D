/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:30:33 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/07 21:59:10 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(int **map, int height)
{
	int	i;

	if (!map)
		return;
	i = 0;
	while (i < height)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

static int **allocate_grid(int height, int width)
{
	int	**grid;
	int	i;
	
	// grid = (int **)ft_calloc(height, sizeof(int *));
	grid = (int **)malloc(sizeof(int *) * height);
	if (!grid)
		return (NULL);
	
	i = 0;
	while (i < height)
	{
		grid[i] = (int *)ft_calloc(width, sizeof(int));
		// grid[i] = (int *)malloc(sizeof(int) * width);
		if (!grid[i])
		{
			while (--i >= 0)
				free(grid[i]);
			free(grid);
			return (NULL);
		}
		// ft_memset(map[i], -2, width * sizeof(int)); //to test
		// ?
		int	j = 0;
		while (j < width)
		{
			grid[i][j] = -2;
			j++;
		}
		i++;
	}
	return (grid);
}

static int	char_to_int(char c) //change this later to use macros/enum and add door
{
	if (c == ' ')
		return (-1);
	else if (c == '1')
		return (1);
	else if (c == '0')
		return (0);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	else
		return (-2);
}

int		**get_2d_map(t_list *map_list, int height, int width)
{
	int		**map_array;
	int		row;
	int		col;
	char	*line;
	
	// map_array = allocate_grid(ft_lstsize(map_list), get_map_width(map_list));
	map_array = allocate_grid(height, width);
	if (!map_array)
		return (NULL);
	row = 0;
	while (map_list) // && row < height)
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

/*
bool check_vertical_isolation(int **map, int width, int height) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (map[y][x] == 0) {
                // Check above unless at the top row
                if (y > 0 && (map[y - 1][x] != 1 && map[y - 1][x] != -1)) {
                    return false;
                }
                // Check below unless at the bottom row
                if (y < height - 1 && (map[y + 1][x] != 1 && map[y + 1][x] != -1)) {
                    return false;
                }
            }
        }
    }
    return true;
}


bool check_vertical_isolation(int **map, int width, int height) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            // Check if the current element is '0'
            if (map[y][x] == 0) {
                // Check the element above unless we're at the top row
                if (y > 0 && (map[y - 1][x] != 1 || map[y - 1][x] == -1)) {
                    return false; // Invalid if above is not '1' or is a space
                }
                // Check the element below unless we're at the bottom row
                if (y < height - 1 && (map[y + 1][x] != 1 || map[y + 1][x] == -1)) {
                    return false; // Invalid if below is not '1' or is a space
                }
            }
        }
    }
    return true; // The map is valid if no '0' is improperly isolated
}
*/