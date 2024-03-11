/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:35:48 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/11 15:08:54 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_minimap	init_minimap(t_cub *cub)
{
	t_minimap	mini;

	ft_memset(&mini, 0, sizeof(t_minimap)); //not necessary if minimap is inside t_cub ? (already memset)
	// 
	mini.img = new_img(cub->mlx, WIDTH / 3, WIDTH / 3, true);
	mini.img->instances->x = WIDTH - mini.img->width; //place on the right
	// 
	mini.round_img = new_img(cub->mlx, WIDTH / 3, WIDTH / 3, true);
	// 
	mini.tile_size = 42;
	// 
	return (mini);

}

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
	else if (value == 2) //door?
		return (HEX_BLUE);
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

static void	draw_tiles(t_minimap *minimap, t_point start, t_point end)
{
	int		x;
	int		y;
	t_point	tile;
	t_point	size;

	// size.x = minimap->tile_size;
	// size.y = minimap->tile_size;
	size.x = minimap->tile_size - 1;
	size.y = minimap->tile_size - 1;
	y = start.y;
	while (y < end.y)
	{
		x = start.x;
		while (x < end.x)
		{
			tile.x = (x - start.x) * minimap->tile_size;
			tile.y = (y - start.y) * minimap->tile_size;
			draw_tile(minimap->img, tile, size, tile_color(y, x));
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */

/* maybe put in libft? */
int	ft_clamp(int value, int min, int max)
{
	return (ft_max(ft_min(value, max), min));
}

static t_point	find_center(t_minimap *minimap, t_map *map)
{
	int			half_width;
	int			half_height;
	t_fpoint	pos;
	t_point		center;

	half_width = minimap->img->width / (2 * minimap->tile_size);
	half_height = minimap->img->height / (2 * minimap->tile_size);
	pos = call_cub()->player.position;
	center.x = ft_clamp((int)pos.x, half_width, map->width - half_width);
	center.y = ft_clamp((int)pos.y, half_height, map->height - half_height);
	return (center);
}

static void	calculate_bounds(t_point center, t_point *start, t_point *end)
{
	int		half_width;
	int		half_height;
	// t_point	center;
	t_minimap	*minimap = &call_cub()->minimap;

	half_width = minimap->img->width / (2 * minimap->tile_size);
	half_height = minimap->img->height / (2 * minimap->tile_size);
	start->x = center.x - half_width;
	start->y = center.y - half_height;
	end->x = center.x + half_width;
	end->y = center.y + half_height;
}

/* ************************************************************************** */ //circle map

static bool	is_in_circle(t_point point, t_point center, int radius)
{
	t_point	distance;

	distance.x = point.x - center.x;
	distance.y = point.y - center.y;
	return ((distance.x * distance.x + distance.y * distance.y) <= radius * radius);
	// return (pow(point.x - center.x, 2) + pow(point.y - center.y, 2)) <= pow(radius, 2);
	
}

static void	make_it_round(t_minimap *minimap, t_map *map)
{
	int		radius = minimap->round_img->width / 3;
	t_point	circle_center = {radius, radius};

	int	map_width = map->width * minimap->tile_size;
	int	map_height = map->height * minimap->tile_size;

	t_fpoint	pos = call_cub()->player.position;

	int	center_offset_x = (int)pos.x - radius;
	int	center_offset_y = (int)pos.y - radius;

	center_offset_x = ft_clamp(center_offset_x, 0, map_width - minimap->round_img->width);
	center_offset_y = ft_clamp(center_offset_y, 0, map_height - minimap->round_img->height);

	int	x;
	int	y;

	y = 0;
	while (y < (int)minimap->round_img->height)
	{
		x = 0;
		while (x < (int)minimap->round_img->width)
		{
			if (is_in_circle((t_point){x, y}, circle_center, radius))
			{
				int	map_x = center_offset_x + x;
				int	map_y = center_offset_y + y;

				int	color = get_pixel(minimap->img, map_x, map_y);
				
				draw_pixel(minimap->round_img, x, y, color);
			}
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */ //features (options)

static int	adjust_tile_size(mlx_image_t *img, t_map *map)
{
	int	tile_width;
	int	tile_height;

	tile_width = img->width / map->width;
	tile_height = img->height / map->height;
	return (ft_min(tile_width, tile_height));
}

static void	features_testing(t_minimap *minimap, t_map *map)
{
	bool	dynamic = false;

	if (dynamic == true)
		minimap->tile_size = adjust_tile_size(minimap->img, map);
	
}

/* ************************************************************************** */

// void	draw_mini_player(t_minimap *minimap, t_player *player)
// {
// 	t_fpoint	line_size;
// 	int			ray_length = 42; //tmp
// 	int			ray_color = 0x00FF00FF; //tmp

// 	line_size.x = player->position.x + player->delta.x * ray_length;
// 	line_size.y = player->position.y + player->delta.y * ray_length;
// 	draw_line(minimap->img, player->position, line_size, ray_color);
// 	draw_circle(minimap->img, player->position, player->size, player->color);
// }

void	draw_minimap(t_minimap *minimap, t_map *map)
{
	t_point	start;
	t_point	end;

	clear_img(minimap->img);
	clear_img(minimap->round_img);
	if (call_cub()->keys.m)
	{
		features_testing(minimap, map);
		calculate_bounds(find_center(minimap, map), &start, &end);
		draw_tiles(minimap, start, end);
		// draw_mini_player(minimap, &call_cub()->player);

		make_it_round(minimap, map);
	}
}



/* maybe use this version for minimap ?
*/
// void	old_update_positionition(t_cub *cub)
// {
// 	t_player	*player;

// 	player = &cub->player;
// 	if (cub->keys.up || cub->keys.w) //move forward
// 	{
// 		player->position.x += player->delta.x * player->speed;
// 		player->position.y += player->delta.y * player->speed;
// 	}
// 	if (cub->keys.a) //move left
// 	{
// 		player->position.x += player->delta.y * player->speed;
// 		player->position.y -= player->delta.x * player->speed;
// 	}
// 	if (cub->keys.down || cub->keys.s) //move backward
// 	{
// 		player->position.x -= player->delta.x * player->speed;
// 		player->position.y -= player->delta.y * player->speed;
// 	}
// 	if (cub->keys.d) //move right
// 	{
// 		player->position.x -= player->delta.y * player->speed;
// 		player->position.y += player->delta.x * player->speed;
// 	}
// }

// void	old_update_player_direction(t_cub *cub)
// {
// 	t_player	*player;

// 	player = &cub->player;
// 	if (cub->keys.left) //turn left
// 	{
// 		player->angle += player->turn_speed;
// 		player->angle = fix_angle(player->angle);
// 		player->delta.x = cos(degree_to_radian(player->angle));
// 		player->delta.y = -sin(degree_to_radian(player->angle));
// 	}
// 	if (cub->keys.right) //turn right
// 	{
// 		player->angle -= player->turn_speed;
// 		player->angle = fix_angle(player->angle);
// 		player->delta.x = cos(degree_to_radian(player->angle));
// 		player->delta.y = -sin(degree_to_radian(player->angle));
// 	}
// }

/* ************************************************************************** */
/* ************************************************************************** */



// void	draw_player2(mlx_image_t *img, t_player *player)
// {
// 	t_fpoint	front;
// 	t_fpoint	left;
// 	t_fpoint	right;
// 	// t_fpoint	base_center;
// 	float	half_base;
	
// 	half_base = player->size * tan(degree_to_radian(30)); // 30 degrees for equilateral triangle

// 	// Front vertex of the triangle
// 	front.x = player->position.x + player->delta.x * player->size;
// 	front.y = player->position.y + player->delta.y * player->size;

// 	// Left and right vertices
// 	left.x = player->position.x - player->delta.y * half_base;
// 	left.y = player->position.y + player->delta.x * half_base;
// 	right.x = player->position.x + player->delta.y * half_base;
// 	right.y = player->position.y - player->delta.x * half_base;

// 	// Calculating the midpoint of the base
// 	// base_center.x = (left.x + right.x) / 2;
// 	// base_center.y = (left.y + right.y) / 2;

// 	draw_triangle(img, front, left, right, player->color);
// 	// draw_line(img, base_center, front, player->color);
// 	// draw_circle_hollow(img, player->position, player->size, 2, HEX_ORANGE);
// }

//

/*
test to fit all map in image
*/
// static void	draw_dynamic_minimap(t_minimap *minimap, t_map *map)
// {
// 	int		x;
// 	int		y;
// 	t_point	tile;
// 	t_point	size;

// 	minimap->tile_size = adjust_tile_size(img, map);
// 	size.x = minimap->tile_size - 1;
// 	size.y = minimap->tile_size - 1;
// 	y = 0;
// 	while (y < map->height)
// 	{
// 		x = 0;
// 		while (x < map->width)
// 		{
// 			tile.x = x * minimap->tile_size;
// 			tile.y = y * minimap->tile_size;
// 			draw_tile(minimap->img, tile, size, tile_color(y, x));
// 			x++;
// 		}
// 		y++;
// 	}
// }
