/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:35:48 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/09 11:01:46 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_minimap	init_minimap(t_cub *cub)
{
	t_minimap	mini;

	ft_memset(&mini, 0, sizeof(t_minimap));
	// 
	mini.img = new_img(cub->mlx, WIDTH, HEIGHT, true);
	// 
	mini.tile_size = 64;
	// 
	mini.player_tile_color = HEX_PURPLE;
	mini.floor_tile_color = HEX_GREEN;
	mini.wall_tile_color = HEX_ORANGE;
	mini.door_tile_color = HEX_BLUE;
	mini.out_tile_color = HEX_GRAY;
	mini.background_color = HEX_BLACK;

	return (mini);

}

/* maybe use this version for minimap ?
*/
// void	old_update_player_position(t_cub *cub)
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

static int	tile_color(t_minimap *minimap, int value)
{
	
	if (value == 0)
		return (minimap->floor_tile_color);
	else if (value == 1)
		return (minimap->wall_tile_color);
	else if (value == 2)
		return (minimap->door_tile_color);
	else if (value == -1 || value == -2)
		return (minimap->out_tile_color);
	else
		return (HEX_RED); //should not get here
}

void	draw_tile(mlx_image_t *img, t_fpoint origin, t_fpoint size, int color)
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
test to fit all map in image
*/
static void	draw_dynamic_minimap(mlx_image_t *img, t_map *map, t_minimap *minimap)
{
	int			x;
	int			y;
	t_fpoint	tile;
	t_fpoint	size;

	int	max_tile_width = img->width / map->width;
	int	max_tile_height = img->height / map->height;

	minimap->tile_size = ft_min(max_tile_width, max_tile_height);
	size.x = minimap->tile_size - 1;
	size.y = minimap->tile_size - 1;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			tile.x = x * minimap->tile_size;
			tile.y = y * minimap->tile_size;
			if (x == (int)call_cub()->player.position.x && y == (int)call_cub()->player.position.y)
				draw_tile(img, tile, size, minimap->player_tile_color);
			else
				draw_tile(img, tile, size, tile_color(minimap, map->map_array[y][x]));
			x++;
		}
		y++;
	}
}

void	draw_minimap(mlx_image_t *img, t_map *map, t_minimap *minimap)
{
	clear_img(img);
	draw_dynamic_minimap(img, map, minimap);
	// int			x;
	// int			y;
	// t_fpoint	tile;
	// t_fpoint	size;
	// int			color;

	// size.x = minimap->tile_size - 1;
	// size.y = minimap->tile_size - 1;
	// y = 0;
	// while (y < map->height)
	// {
	// 	x = 0;
	// 	while (x < map->width)
	// 	{
	// 		tile.x = x * minimap->tile_size;
	// 		tile.y = y * minimap->tile_size;
	// 		if (map->map_array[y][x] == 1)
	// 			color = minimap->wall_tile_color;
	// 		else
	// 			color = minimap->floor_tile_color;
	// 		draw_tile(img, tile, size, color);
	// 		x++;
	// 	}
	// 	y++;
	// }
}

/*
tests for more intricate minimap display
*/

// void	draw_round_minimap(mlx_image_t *main_img, mlx_img_t *minimap_img, t_fpoint minimap_center, int radius)
// {
// 		int	x;
// 		int	y;
// 		int	distance_squared;
// 		int color;

// 		y = 0;
// 		while (y < minimap_img->height)
// 		{
// 			y++;
// 			x = 0;
// 			while (x < minimap_img->width)
// 			{
// 				distance_squared = (x - minimap_center.x) * (x - minimap_center.x) + (y - minimap_center.y) * (y - minimap_center.y);
				
// 				if (distance_squared <= radius * radius)
// 				{
// 					// pixel is in circle, draw from minimap
// 					color = get_pixel(minimap_img, x, y);
// 					draw_pixel(main_img, x + minimap_center.x - radius, y + minimap_center.y - radius, color);
// 				}
// 				else
// 				{
// 					// pixel is outside the circle, draw from main image
// 					// not necessary if main img is already drawn and the minimap is drawn over it
// 				}
// 				x++;
// 			}
// 		}
// }

/*
1. prepare the large map image

set enable = false;

2. create minimap image, will serve as minimap overlay
where we will draw the portion of the large map image centered around the player's current pos

3. update minimap based on player movement
*do we have a different struct 't_miniplayer' ?

when the player moves (hooks)
	- calculate the source coordinates
	based on the player's position on the large map, calculate top left coord of the portion of the large map img we want to display on the minimap
	(centered around the player's position)
	
	- copy pixels from large image to minimap image (using the circular effect to copy the source pixels from large map if in circle)

	- draw if boolean is toggled
*/

// void	render_minimap(mlx_image_t *full_map_img, mlx_image_t *minimap_img, mlx_image_t *main_img, t_player player, int radus)
// {
//     int sourceX = player.x - minimap_img->width / 2;
//     int sourceY = player.y - minimap_img->height / 2;

//     // Adjust sourceX and sourceY if they go out of bounds of the large_map_img

//     for (int y = 0; y < minimap_img->height; y++) {
//         for (int x = 0; x < minimap_img->width; x++) {
//             int largeMapX = sourceX + x;
//             int largeMapY = sourceY + y;

//             // Copy pixel from large_map_img to minimap_img, or from main_img if outside the circular area
//             int color;
//             if (is_inside_circle(x, y, radius)) {
//                 color = get_pixel(large_map_img, largeMapX, largeMapY);
//             } else {
//                 color = get_pixel(main_img, largeMapX, largeMapY); // Adjust coordinates as needed
//             }
//             draw_pixel(minimap_img, x, y, color);
//         }
//     }

//     // Optionally, draw minimap_img onto the main window
// }



	// // assuming the minimap is a square
	// t_fpoint	center;

	// center.x = minimap_img->width / 2;
	// center.y = minimap_img->height / 2;

	// // [...]while y<height, while x<width
	// if (is_inside_circle((t_fpoint){x, y}, center, radius))
	// 	// the point(x, y) is inside the circle
	// else
	// 	// it is outside the circle

/* ************************************************************************** */

// void	draw_player(mlx_image_t *img, t_player *player)
// {
// 	t_fpoint	line_size;
// 	int		ray_length = 42; //tmp
// 	int		ray_color = 0x00FF00FF; //tmp

// 	line_size.x = player->position.x + player->delta.x * ray_length;
// 	line_size.y = player->position.y + player->delta.y * ray_length;
// 	draw_line(img, player->position, line_size, ray_color);
// 	draw_circle(img, player->position, player->size, player->color);
// }

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
