/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:30:33 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/04 10:53:08 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	store_map_line(t_list **map_list, char *line)
{
	t_list	*node;

	node = ft_lstnew(ft_strtrim(line, "\n"));
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

//

static int	char_to_int(char c) //change this later
{
	if (c == ' ')
		return (SPACE);
	else if (c == '1')
		return (WALL);
	else if (c == '0')
		return (UNVISITED);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (UNVISITED);
	else
		return (INVALID);
}

static int **allocate_map(int height, int width)
{
	int	**map;
	int	i;
	
	map = (int **)ft_calloc(height, sizeof(int *));
	if (!map)
	{
		// error: map allocation
		return (NULL);
	}
	i = 0;
	while (i < height)
	{
		map[i] = (int *)ft_calloc(width, sizeof(int));
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			// error: map row allocation
			return (NULL);
		}
		i++;
	}
	return (map);
}

int	**get_2d_map(t_list *map_list, int height, int width, t_point *start_position)
{
	int		**map;
	int		row;
	int		col;
	char	*line;

	map = allocate_map(height, width);
	if (!map)
		return (NULL);
	
	int	start_count = 0;
	row = 0;
	while (row < height && map_list)
	{
		line = (char *)map_list->content;
		col = 0;
		while (col < width && line[col])
		{
			int	value = char_to_int(line[col]);
			if (value == INVALID)
			{
				free_map(map, height);
				return (NULL);
			}
			if (ft_strchr("NSEW", line[col]))
			{
				start_count++;
				if (start_count > 1)
				{
					free_map(map, height);
					return (NULL);
				}
				// player-> or scene->spawn_orientation = line[col];
				start_position->x = col;
				start_position->y = row;
			}
			map[row][col] = value;
			col++;
		}
		row++;
		map_list = map_list->next;
	}
	if (start_count != 1)
	{
		free_map(map, height);
		return (NULL);
	}
	return (map);
}

//

void	flood_fill(int **map, int x, int y, int height, int width)
{
	if (x < 0 || x >= width || y < 0 || y >= height || map[y][x] != UNVISITED)
		return;
	
	map[y][x] = 0; //mark as accessible/visited

	flood_fill(map, x + 1, y, height, width);
	flood_fill(map, x - 1, y, height, width);
	flood_fill(map, x , y + 1, height, width);
	flood_fill(map, x , y - 1, height, width);
}

int	validate_flood_fill(int **map, int height, int width)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if ((x == 0 || x == width -1 || y == 0 || y == height -1) && map[y][x] == 0)
			{
				// error: map leaks at the border
				// add logic for smaller row or col *!!!
				return (FALSE);
			}
			if (map[y][x] == UNVISITED)
			{
				// error ? or not.. (Unvisited accessible area found within the map)
				return (FALSE);
			}
			x++;
		}
		y++;
	}
	return (TRUE);
}
