/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:39:54 by oroy              #+#    #+#             */
/*   Updated: 2024/05/01 21:50:22 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_asset(t_asset *asset)
{
	t_cub	*cub;
	int		i;

	cub = call_cub();
	if (asset->is_animated)
	{
		i = 0;
		while (i < asset->anim.last_frame - 1)
		{
			mlx_delete_image(cub->mlx, asset->anim.frames[i]);
			free(asset->anim.frames[i]);
			i++;
		}
		free(asset->anim.frames);
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
