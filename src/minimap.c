/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:13:03 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/26 22:11:04 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	init_map(t_scene *scene)
{
	t_map	map;

	map.tile_size = 64;
	map.width = 8;
	map.height = 8;
	// map.floor_color = HEX_GROUND;
	map.floor_color = rgb_to_int(scene->floor);
	// map.ceiling_color = HEX_SKY;
	map.ceiling_color = rgb_to_int(scene->ceiling);
	map.wall_tile_color = HEX_BLACK;
	map.floor_tile_color = HEX_WHITE;
	map.background_color = HEX_GRAY;
	return (map);
}

void	draw_tile(mlx_image_t *img, t_point origin, t_point size, int color)
{
	int	x;
	int	y;

	y = origin.y;
	while (y < origin.y + size.y)
	{
		x = origin.x;
		while (x < origin.x + size.x)
		{
			draw_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

/*
tmp map to test
*/
void	draw_minimap(mlx_image_t *img, t_map *map)
{
	int		x;
	int		y;
	t_point	tile;
	t_point	size;
	int		color;
	// 
	int		tmp_map[] = 
	{
		1,1,1,1,1,1,1,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,1,0,1,
		1,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,
	};
	//
	size.x = map->tile_size - 1;
	size.y = map->tile_size - 1;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			tile.x = x * map->tile_size;
			tile.y = y * map->tile_size;
			if (tmp_map[y * map->width + x] == 1)
				color = map->wall_tile_color;
			else
				color = map->floor_tile_color;
			draw_tile(img, tile, size, color);
			x++;
		}
		y++;
	}
}
