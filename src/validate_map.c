/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:57:06 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/18 17:46:11 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO: insert elevator verification *!!

/*
11111111111
10000000001
10111111101
101 11  101
101 11  111
101101   11
100001    1
111111

** ' ' will be '-1' **

if [][] == '0', up must be 0 or 1 (or 2 or 3),
	down must be 0 or 1 (or 2 or 3)
if [][] == ' ', up must be ' ' or 1,
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
		if (up >= current && down >= current)
			return (true);
		else
			return (false);
	}
	if (current == -1)
	{
		if ((up == current || up == 1 || up == -2) \
		&& (down == current || down == 1 || down == -2))
			return (true);
		else
			return (false);
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
}
