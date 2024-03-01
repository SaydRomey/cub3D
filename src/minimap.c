/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:13:03 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/29 21:57:54 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_2d_array(int **array, int rows, int cols)
{
	int	i = 0;
	int	j = 0;

	while (i < rows)
	{
		while (j < cols)
		{
			printf("%2d ", array[i][j]);
			j++;
		}
		i++;
	}
	ft_printf("\n");
}

t_map	init_map(t_scene *scene)
{
	t_map	map;
	t_list	*map_list;
	t_point	start_position; //tmp

	map_list = scene->map_list;
	ft_memset(&map, 0, sizeof(t_map));

	map.width = get_map_width(map_list);
	map.height = get_map_height(map_list);
	map.map_array = get_2d_map(scene->map_list, map.height, map.width, &start_position);

	map.tile_size = 24;
	// map.tile_size = 64;
	// map.width = 8;
	// map.height = 8;
	// map.floor_color = HEX_GROUND;
	map.floor_color = get_color(scene, FLOOR);
	// map.ceiling_color = HEX_SKY;
	map.ceiling_color = get_color(scene, CEILING);
	map.wall_tile_color = HEX_BLACK;
	map.floor_tile_color = HEX_WHITE;
	map.background_color = HEX_GRAY;

	print_2d_array(map.map_array, map.height, map.width);
	
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
	// int		tmp_map[] = 
	// {
	// 	1,1,1,1,1,1,1,1,
	// 	1,0,1,0,0,0,0,1,
	// 	1,0,1,0,0,0,0,1,
	// 	1,0,1,0,0,0,0,1,
	// 	1,0,0,0,0,0,0,1,
	// 	1,0,0,0,0,1,0,1,
	// 	1,0,0,0,0,0,0,1,
	// 	1,1,1,1,1,1,1,1,
	// };
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
			if (map->map_array[y][x] == 1)
			// if (tmp_map[y * map->width + x] == 1)
				color = map->wall_tile_color;
			else
				color = map->floor_tile_color;
			draw_tile(img, tile, size, color);
			x++;
		}
		y++;
	}
}

/*
tests for more intricate minimap display
*/

// void	draw_round_minimap(mlx_image_t *main_img, mlx_img_t *minimap_img, t_point minimap_center, int radius)
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
	// t_point	center;

	// center.x = minimap_img->width / 2;
	// center.y = minimap_img->height / 2;

	// // [...]while y<height, while x<width
	// if (is_inside_circle((t_point){x, y}, center, radius))
	// 	// the point(x, y) is inside the circle
	// else
	// 	// it is outside the circle
