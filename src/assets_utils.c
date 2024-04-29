/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:39:54 by oroy              #+#    #+#             */
/*   Updated: 2024/04/29 14:10:11 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_near_elevator(t_map *map, int x, int y)
{
	if (map->map_array[y][x] == ELEVATOR
		|| map->map_array[y][x + 1] == ELEVATOR
		|| map->map_array[y - 1][x + 1] == ELEVATOR
		|| map->map_array[y - 1][x] == ELEVATOR
		|| map->map_array[y - 1][x - 1] == ELEVATOR
		|| map->map_array[y][x - 1] == ELEVATOR
		|| map->map_array[y + 1][x - 1] == ELEVATOR
		|| map->map_array[y + 1][x] == ELEVATOR
		|| map->map_array[y + 1][x + 1] == ELEVATOR)
		return (true);
	else
		return (false);
}

// bool	is_near_elevator(t_map *map, int x, int y)
// {
// 	int	dy;
// 	int	dx;

// 	dy = -1;
// 	while (dy <= 1)
// 	{
// 		dy++;
// 		dx = -1;
// 		while (dx <= -1)
// 		{
// 			if (map->map_array[y + dy][x + dx] == ELEVATOR)
// 				return (true);
// 			dx++;
// 		}
// 		return (false);
// 	}
// }

// bool	is_near_elevator(t_map *map, int x, int y)
// {
// 	int	dy;
// 	int	dx;
// 	int	nx;
// 	int	ny;

// 	dy = -1;
// 	while (dy <= 1)
// 	{
// 		dy++;
// 		dx = -1;
// 		while (dx <= -1)
// 		{
// 			nx = x + dx;
// 			ny = y + dy;
// 			if (nx >= 0 && nx < map->width && ny >= 0 && ny < map->height)
// 			{
// 				if (map->map_array[ny][nx] == ELEVATOR)
// 				{
// 					return (true);
// 				}
// 			}
// 			dx++;
// 		}
// 		return (false);
// 	}
// }
