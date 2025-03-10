/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:24:25 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/09 18:42:05 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	look into this **

*/
static void	adjust_tile_size(t_minimap *mini, t_map *map, int margin_tiles)
{
	int	available_width;
	int	available_height;
	int	tile_width;
	int	tile_height;
	int	tile_size;

	if (margin_tiles * 2 == map->width || margin_tiles * 2 == map->height)
	{
		tile_width = mini->img->width / (map->width + 1);
		tile_height = mini->img->height / (map->height + 1);	
	}
	else
	{
		tile_width = mini->img->width / map->width;
		tile_height = mini->img->height / map->height;
	}
	tile_size = ft_min(tile_width, tile_height);
	if (margin_tiles > 0)
	{
		available_width = mini->img->width - (margin_tiles * 2 * tile_size);
		available_height = mini->img->height - (margin_tiles * 2 * tile_size);
		tile_width = available_width / map->width;
		tile_height = available_height / map->height;
		tile_size = ft_min(tile_width, tile_height);
	}
	mini->tile_size = tile_size;
}

static t_point	find_center(t_minimap *mini)
{
	t_point		center;

	mini->half_width = mini->img->width / (2 * mini->tile_size);
	mini->half_height = mini->img->height / (2 * mini->tile_size);
	center.x = mini->half_width;
	center.y = mini->half_height;
	return (center);
}

static t_point	find_offset(t_minimap *mini, t_map *map)
{
	int		total_minimap_width;
	int		total_minimap_height;
	t_point	offset;

	total_minimap_width = mini->tile_size * map->width;
	total_minimap_height = mini->tile_size * map->height;
	offset.x = (WIDTH - total_minimap_width) / 2;
	offset.y = (HEIGHT - total_minimap_height) / 2;
	return (offset);
}

t_minimap	init_minimap(t_map *map)
{
	t_minimap	mini;

	ft_memset(&mini, 0, sizeof(t_minimap));
	mini.img = new_img(call_cub()->mlx, WIDTH, HEIGHT, false);
	adjust_tile_size(&mini, map, 2);
	mini.center = find_center(&mini);
	mini.offset = find_offset(&mini, map);
	set_minimap_colors(map, mini.colors);
	return (mini);
}
