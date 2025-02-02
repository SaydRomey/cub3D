/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:39:54 by oroy              #+#    #+#             */
/*   Updated: 2024/05/02 15:41:57 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_asset(t_asset *asset)
{
	if (asset->is_animated)
	{
		free_animation(&asset->anim);
	}
	free(asset);
}

void	asset_pixel(mlx_image_t *img, int x, int y, int color)
{
	if (get_alpha(color) == 255)
		draw_pixel(img, x, y, color);
}

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
