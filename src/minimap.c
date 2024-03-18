/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:24:25 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/17 13:08:20 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	tile_color(int y, int x)
{
	int			value;
	t_fpoint	position;

	value = call_cub()->map.map_array[y][x];
	position = call_cub()->player.position;

	if (x == (int)position.x && y == (int)position.y)
		return (HEX_PURPLE);
	else if (value == 0)
		return (HEX_GREEN);
	else if (value == 1)
		return (HEX_ORANGE);
	else if (value == 2) //DOOR
		return (HEX_BLUE);
	else if (value == 3) //ELEVATOR
		return (HEX_OLILAS);
	else if (value == -1 || value == -2)
		return (HEX_GRAY);
	else
		return (HEX_RED); //should not get here
}

static void	draw_tile(mlx_image_t *img, t_point origin, t_point size, int color)
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

static void	draw_tiles(t_minimap *mini, t_point start, t_point end)
{
	t_map	*map = &call_cub()->map;
	int		x;
	int		y;
	t_point	tile;
	t_point	size = {.x = mini->tile_size - 1, .y = mini->tile_size - 1};

	y = start.y;
	while (y < end.y)
	{
		x = start.x;
		while (x < end.x)
		{
			tile.x = (x - start.x) * mini->tile_size;
			tile.y = (y - start.y) * mini->tile_size;
			if (x >= 0 && x < map->width && y >= 0 && y < map->height)
				draw_tile(mini->img, tile, size, tile_color(y, x));
			x++;
		}
		y++;
	}
}


// static int	adjust_tile_size(mlx_image_t *img, t_map *map)
// {
// 	int	tile_width;
// 	int	tile_height;

// 	tile_width = img->width / map->width;
// 	tile_height = img->height / map->height;
// 	return (ft_min(tile_width, tile_height));
// }


void	draw_minimap(t_minimap *mini, t_map *map)
{
	draw_background(mini->img, HEX_BLACK);

	(void)map;

	draw_tiles()

	// iso_test(mini);
	// iso_grid(mini);


	
}
t_minimap	init_minimap(t_cub *cub)
{
	t_minimap	mini;
	int			width = WIDTH;
	int			height = HEIGHT;

	mini.img = new_img(cub->mlx, width, height, true);
	move_img(mini.img, WIDTH - width, HEIGHT - height);
	mini.tile_size = TILE_SIZE;
	
	return (mini);
}
