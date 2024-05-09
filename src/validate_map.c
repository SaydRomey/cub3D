/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:57:06 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/02 17:14:57 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_elevator(t_map *map)
{
	t_point	pos;

	if (there_is_a_problem())
		return ;
	if (!find_value_in_array(map, ELEVATOR, &pos))
		return ;
	if (has_duplicate(map, ELEVATOR))
	{
		set_error("More than one elevator found in map");
	}
	else if (get_elevator_orientation(map->map_array, &pos) == -1)
	{
		set_error("Invalid elevator");
	}
}

/*
11111111111
10000000001
10111111101
101 11  101
101 11  111111
101101   11
100001    1
111111 11

** ' ' will be '-1' **

if [y][x] == '0',
	up must be 0 or 1
	down must be 0 or 1
if [y][x] == ' ',
	up must be ' ' or 1
	down must be ' ' or 1
*/
static bool	check_vertical(int **map_array, int y, int x)
{
	int	current;
	int	up;
	int	down;

	current = map_array[y][x];
	up = map_array[y - 1][x];
	down = map_array[y + 1][x];
	if (current == 0)
	{
		return (up >= current && down >= current);
	}
	else if (current == -1)
	{
		return ((up == current || up == 1 || up == -2) \
		&& (down == current || down == 1 || down == -2));
	}
	return (true);
}

static bool	columns_are_valid(int **map_array, int width, int height)
{
	int	x;
	int	y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			if (y > 0 && y < height - 1)
				if (!check_vertical(map_array, y, x))
					return (false);
			y++;
		}
		x++;
	}
	return (true);
}

void	validate_map(t_map *map)
{
	if (there_is_a_problem())
		return ;
	if (!columns_are_valid(map->map_array, map->width, map->height))
		set_error("Invalid array column");
	if (BONUS)
	{
		validate_elevator(map);
	}
}
