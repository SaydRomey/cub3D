/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_og.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:35:48 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/15 15:26:19 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_minimap(t_cub *cub, t_minimap *minimap)
{
	// Convert player's position to minimap coordinates
	t_fpoint	minimap_pos = 
	{
		.x = (cub->player.position.x / cub->map.width) * minimap->width,
		.y = (cub->player.position.y / cub->map.height) * minimap->height
	};

	// Convert player's orientation to a visual indicator on the minimap
	t_fpoint minimap_dir = 
	{
		.x = cos(degree_to_radian(cub->player.angle)) * line_maybe,
		.y = -sin(degree_to_radian(cub->player.angle)) * line_maybe
	};

	// Update the minimap with the player's position and direction
	draw_player_on_minimap(minimap, &minimap_pos, &minimap_dir);
}

//

t_minimap	init_minimap(t_cub *cub)
{
	t_minimap	mini;
	int			width = 500;
	int			height = 500;

	ft_memset(&mini, 0, sizeof(t_minimap));
	// 
	mini.img = new_img(cub->mlx, width, height, true);
	move_img(mini.img, WIDTH - (mini.img->width - TILE_SIZE), TILE_SIZE);
	// move_img(mini.img, (WIDTH - mini.img->width) / 2, (HEIGHT - mini.img->height) / 2);
	// 
	mini.round_img = new_img(cub->mlx, width, height, true);
	move_img(mini.round_img, WIDTH - (mini.round_img->width - TILE_SIZE), TILE_SIZE);
	// move_img(mini.round_img, (WIDTH - mini.round_img->width) / 2, (HEIGHT - mini.round_img->height) / 2);
	// 
	mini.tile_size = TILE_SIZE;
	mini.radius = ft_min(mini.round_img->width, mini.round_img->height) / 2;
	mini.center.x = mini.round_img->width / 2;
	mini.center.y = mini.round_img->height / 2;
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

static void	draw_tiles(t_minimap *mini, t_point start, t_point end)
{
	int		x;
	int		y;
	t_point	tile;
	t_point	size;

	t_map	*map = &call_cub()->map;
	size.x = mini->tile_size - 1;
	size.y = mini->tile_size - 1;
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

/* ************************************************************************** */

static t_point	find_center(t_minimap *mini, t_map *map)
{
	int			half_width;
	int			half_height;
	t_fpoint	pos;
	t_point		center;

	half_width = mini->img->width / (2 * mini->tile_size);
	half_height = mini->img->height / (2 * mini->tile_size);
	pos = call_cub()->player.position;
	center.x = ft_clamp((int)pos.x, half_width, map->width - half_width);
	center.y = ft_clamp((int)pos.y, half_height, map->height - half_height);
	return (center);
}

static void	calculate_bounds(t_point center, t_point *start, t_point *end)
{
	int			half_width;
	int			half_height;
	t_minimap	*mini = &call_cub()->minimap;
	t_map		*map = &call_cub()->map;

	half_width = mini->img->width / (2 * mini->tile_size);
	half_height = mini->img->height / (2 * mini->tile_size);

	start->x = ft_max(0, center.x - half_width);
	start->y = ft_max(0, center.y - half_height);
	end->x = ft_min(map->width, center.x + half_width);
	end->y = ft_min(map->height, center.y + half_height);

	start->x = center.x - half_width;
	start->y = center.y - half_height;

	end->x = center.x + half_width;
	end->y = center.y + half_height; //this seems to give the same result ?
}

/* ************************************************************************** */ //circle map

/*
applies a circular mask when copying existing minimap
*/
static void	make_it_round(t_minimap *mini, t_map *map)
{
	int		radius = mini->round_img->width / 3;
	t_point	circle_center = {radius, radius};

	int	map_width = map->width * mini->tile_size;
	int	map_height = map->height * mini->tile_size;

	t_fpoint	pos = call_cub()->player.position;

	int	center_offset_x = (int)pos.x - radius;
	int	center_offset_y = (int)pos.y - radius;

	center_offset_x = ft_clamp(center_offset_x, 0, map_width - mini->round_img->width);
	center_offset_y = ft_clamp(center_offset_y, 0, map_height - mini->round_img->height);

	int	x;
	int	y;

	y = 0;
	while (y < (int)mini->round_img->height)
	{
		x = 0;
		while (x < (int)mini->round_img->width)
		{
			if (is_in_circle((t_point){x, y}, circle_center, radius))
			{
				int	map_x = center_offset_x + x;
				int	map_y = center_offset_y + y;

				int	color = get_pixel(mini->img, map_x, map_y);
				draw_pixel(mini->round_img, x, y, color);
			}
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */ //features (options)

static int	adjust_tile_size(mlx_image_t *img, t_map *map) //fits all the tiles in the map
{
	int	tile_width;
	int	tile_height;

	tile_width = img->width / map->width;
	tile_height = img->height / map->height;
	return (ft_min(tile_width, tile_height));
}

static void	setup_visibility(t_minimap *mini)
{
	if (mini->options.visible == false)
	{
		mini->img->instances->enabled = false;
		mini->round_img->instances->enabled = false;
	}
	else
	{
		mini->img->instances->enabled = mini->options.rectangular;
		mini->round_img->instances->enabled = mini->options.round;
	}
}

static void	update_options(t_minimap *mini, t_options *options)
{
	t_keys		keys;

	keys = call_cub()->keys;
	
	options->visible = keys.m;

	options->dynamic_tile_size = keys.two;
	options->rectangular = !keys.one;
	options->round = keys.one; // = !options->rectangular
	
	setup_visibility(mini);
}

static void	features_testing(t_minimap *mini, t_map *map)
{
	t_options	options;

	options = mini->options;

	if (options.rectangular && options.dynamic_tile_size)
		mini->tile_size = adjust_tile_size(mini->img, map);
	else
		mini->tile_size = TILE_SIZE;
}

/* ************************************************************************** */ //wip tests

void	rotate_image(mlx_image_t *src, mlx_image_t *dst, double angle)
{
	int		x;
	int		y;
	int		new_x;
	int		new_y;
	int		center_x;
	int		center_y;
	double	cos_a;
	double	sin_a;

	center_x = src->width / 2;
	center_y = src->height / 2;
	cos_a = cos(angle);
	sin_a = sin(angle);

	y = 0;
	while (y < dst->height)
	{
		x = 0;
		while (x < dst->width)
		{
			new_x = (int)((x - center_x) * cos_a - (y - center_y) * sin_a) + center_x;
			new_y = (int)((x - center_x) * sin_a + (y - center_y) * cos_a) + center_y;
			draw_pixel(dst, x, y, get_pixel(src, new_x, new_y));
			x++;
		}
		y++;
	}
}

void	draw_mini_player(t_minimap *mini, t_player *player)
{
	t_fpoint	line_size;
	int			ray_length = 42; //tmp
	int			ray_color = 0x00FF00FF; //tmp

	line_size.x = player->position.x + player->delta.x * ray_length;
	line_size.y = player->position.y + player->delta.y * ray_length;
	draw_line(mini->img, player->position, line_size, ray_color);
	draw_circle(mini->img, player->position, player->size, player->color);
}

void	draw_minimap(t_minimap *mini, t_map *map)
{
	t_point	start;
	t_point	end;

	clear_img(mini->img);
	clear_img(mini->round_img);

	// fill_img(mini->img, 242);
	// fill_img(mini->round_img, 242);
	
	update_options(mini, &mini->options);
	features_testing(mini, map);

	calculate_bounds(find_center(mini, map), &start, &end);
	draw_tiles(mini, start, end);
	make_it_round(mini, map);
}

//////////////////////////////////////


void draw_minimap(t_minimap *mini, t_map *map)
{
	t_point start, end;

	clear_img(mini->img);
	clear_img(mini->round_img);
	
	if (call_cub()->keys.m)
	{
		features_testing(minimap, map);
		t_point center = find_center(minimap, map);
		calculate_bounds(center, &start, &end, minimap, map); // Adjusted function call
		draw_tiles(minimap, start, end);
		draw_mini_player(minimap, &call_cub()->player);

		make_it_round(minimap, map);
	}
}


////////////////////////////////////////


/* maybe use this version for minimap ?
*/
void	old_update_positionition(t_cub *cub)
{
	t_player	*player;

	player = &cub->player;
	if (cub->keys.up || cub->keys.w) //move forward
	{
		player->position.x += player->delta.x * player->speed;
		player->position.y += player->delta.y * player->speed;
	}
	if (cub->keys.a) //move left
	{
		player->position.x += player->delta.y * player->speed;
		player->position.y -= player->delta.x * player->speed;
	}
	if (cub->keys.down || cub->keys.s) //move backward
	{
		player->position.x -= player->delta.x * player->speed;
		player->position.y -= player->delta.y * player->speed;
	}
	if (cub->keys.d) //move right
	{
		player->position.x -= player->delta.y * player->speed;
		player->position.y += player->delta.x * player->speed;
	}
}

void	old_update_player_direction(t_cub *cub)
{
	t_player	*player;

	player = &cub->player;
	if (cub->keys.left) //turn left
	{
		player->angle += player->turn_speed;
		player->angle = fix_angle(player->angle);
		player->delta.x = cos(degree_to_radian(player->angle));
		player->delta.y = -sin(degree_to_radian(player->angle));
	}
	if (cub->keys.right) //turn right
	{
		player->angle -= player->turn_speed;
		player->angle = fix_angle(player->angle);
		player->delta.x = cos(degree_to_radian(player->angle));
		player->delta.y = -sin(degree_to_radian(player->angle));
	}
}

/* ************************************************************************** */
/* ************************************************************************** */

void	draw_player2(mlx_image_t *img, t_player *player)
{
	t_fpoint	front;
	t_fpoint	left;
	t_fpoint	right;
	// t_fpoint	base_center;
	float	half_base;
	
	half_base = player->size * tan(degree_to_radian(30)); // 30 degrees for equilateral triangle

	// Front vertex of the triangle
	front.x = player->position.x + player->delta.x * player->size;
	front.y = player->position.y + player->delta.y * player->size;

	// Left and right vertices
	left.x = player->position.x - player->delta.y * half_base;
	left.y = player->position.y + player->delta.x * half_base;
	right.x = player->position.x + player->delta.y * half_base;
	right.y = player->position.y - player->delta.x * half_base;

	// Calculating the midpoint of the base
	// base_center.x = (left.x + right.x) / 2;
	// base_center.y = (left.y + right.y) / 2;

	draw_triangle(img, front, left, right, player->color);
	// draw_line(img, base_center, front, player->color);
	// draw_circle_hollow(img, player->position, player->size, 2, HEX_ORANGE);
}



/*
test to fit all map in image
*/
static void	draw_dynamic_minimap(t_minimap *mini, t_map *map)
{
	int		x;
	int		y;
	t_point	tile;
	t_point	size;

	mini->tile_size = adjust_tile_size(img, map);
	size.x = mini->tile_size - 1;
	size.y = mini->tile_size - 1;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			tile.x = x * mini->tile_size;
			tile.y = y * mini->tile_size;
			draw_tile(mini->img, tile, size, tile_color(y, x));
			x++;
		}
		y++;
	}
}
