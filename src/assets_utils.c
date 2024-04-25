/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:39:54 by oroy              #+#    #+#             */
/*   Updated: 2024/04/24 20:51:10 by oroy             ###   ########.fr       */
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
