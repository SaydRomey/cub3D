/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:35:48 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/06 15:41:49 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
tmp map to test
*/
// void	draw_minimap(mlx_image_t *img, t_map *map)
// {
// 	int		x;
// 	int		y;
// 	t_fpoint	tile;
// 	t_fpoint	size;
// 	int		color;
// 	// 
// 	// int		tmp_map[] = 
// 	// {
// 	// 	1,1,1,1,1,1,1,1,
// 	// 	1,0,1,0,0,0,0,1,
// 	// 	1,0,1,0,0,0,0,1,
// 	// 	1,0,1,0,0,0,0,1,
// 	// 	1,0,0,0,0,0,0,1,
// 	// 	1,0,0,0,0,1,0,1,
// 	// 	1,0,0,0,0,0,0,1,
// 	// 	1,1,1,1,1,1,1,1,
// 	// };
// 	//
// 	size.x = map->tile_size - 1;
// 	size.y = map->tile_size - 1;
// 	y = 0;
// 	while (y < map->height)
// 	{
// 		x = 0;
// 		while (x < map->width)
// 		{
// 			tile.x = x * map->tile_size;
// 			tile.y = y * map->tile_size;
// 			if (map->map_array[y][x] == 1)
// 			// if (tmp_map[y * map->width + x] == 1)
// 				color = map->wall_tile_color;
// 			else
// 				color = map->floor_tile_color;
// 			draw_tile(img, tile, size, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

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
1. prepare the large map pimage

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

