/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:10:08 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/22 20:10:15 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
if 'value_to_find' is found in 'map->map_array',
will set the column and row in 'point_ptr' and return true
else will return false
*/
bool	find_value_in_array(t_map *map, int value_to_find, t_point *point_ptr)
{
	int		y;
	int		x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map_array[y][x] == value_to_find)
			{
				*point_ptr = (t_point){x, y};
				return (true);
			}
			x++;
		}
		y++;
	}
	return (false);
}

bool	has_duplicate(t_map *map, int value_to_find)
{
	int		y;
	int		x;
	bool	found;

	found = false;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map_array[y][x] == value_to_find)
			{
				if (found)
					return (true);
				else
					found = true;
			}
			x++;
		}
		y++;
	}
	return (false);
}
