/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:11:30 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/15 15:11:57 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// implement the player pos tile drawing, since minimap is not drawn in each frame now..

/* ************************************************************************** */
static int	tile_color(t_map *map, int y, int x)
{
	int			value;
	// t_fpoint	position;

	value = map->map_array[y][x];
	// position = call_cub()->player.position;

	// if (x == (int)position.x && y == (int)position.y)
	// 	return (HEX_PURPLE);

	if (value < 0)
		return (HEX_GRAY);
	else if (value == 0) //WALKABLE
		return (HEX_GROUND);
	else if (value == 1) //WALL
		return (HEX_BLACK);
	else if (value == 2) //DOOR
		return (HEX_BLUE);
	else if (value == 3) //ELEVATOR
		return (HEX_OLILAS);
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

static void	draw_tiles(t_minimap *mini, t_map *map, t_point start, t_point end)
{
	int		x;
	int		y;
	t_point	tile;
	t_point	size;

	size.x = mini->tile_size - 1;
	size.y = mini->tile_size - 1;
	y = start.y;
	while (y < end.y)
	{
		x = start.x;
		while (x < end.x)
		{
			tile.x = ((x - start.x) * mini->tile_size) + mini->offset.x;
			tile.y = ((y - start.y) * mini->tile_size) + mini->offset.y;
			if (x >= 0 && x < map->width && y >= 0 && y < map->height)
				draw_tile(mini->img, tile, size, tile_color(map, y, x));
			x++;
		}
		y++;
	}
}

static void	calculate_bounds(t_minimap *mini, t_map *map, t_point *start, t_point *end)
{
	int		half_width;
	int		half_height;
	
	half_width = mini->img->width / (2 * mini->tile_size);
	half_height = mini->img->height / (2 * mini->tile_size);

	start->x = ft_max(0, mini->center.x - half_width);
	start->y = ft_max(0, mini->center.y - half_height);
	end->x = ft_min(map->width, mini->center.x + half_width + 1);
	end->y = ft_min(map->height, mini->center.y + half_height + 1);
}

/*
draws a full size minimap once,
** will serve as a reference for radar minimap

*/
void	draw_minimap(t_minimap *mini, t_map *map)
{
	t_point	start;
	t_point	end;
	
	calculate_bounds(mini, map, &start, &end);
	draw_tiles(mini, map, start, end);
}
