/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:19:45 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/15 20:39:49 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_square(t_img *img, t_point origin, t_point size, int color)
{
	int x;
	int y;

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

/* tmp map to test */

void	draw_mini_map(t_img *img, t_map *map)
{
	int		x;
	int		y;
	t_point	origin;
	t_point	size;
	int		color;
	// 
	int	tmp_map[] = 
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
	y = 0;
	size.x = map->tile_size - 1;
	size.y = map->tile_size - 1;
	while (y < map->map_y)
	{
		x = 0;
		while (x < map->map_x)
		{
			origin.x = x * map->tile_size;
			origin.y = y * map->tile_size;
			if (tmp_map[y * map->map_x + x] == 1)
				color = map->wall_color;
			else
				color = map->floor_color;
			// draw_rectangle(img, origin, size, color);
			draw_square(img, origin, size, color);
			x++;
		}
		y++;
	}
}

// void draw_mini_map(t_img *img)
// {
//     int x, y, xo, yo, xi, yi;
//     int color;
//     int squareSize = mapS - 1; // Reducing the square size by one pixel
	
// 	// 
// 	t_point	origin = {0, 0};
// 	t_point	end = {WIDTH, HEIGHT};
// 	draw_rectangle(img, origin, end, HEX_BROWN);
// 	// 
//     for (y = 0; y < mapY; y++)
// 	{
//         for (x = 0; x < mapX; x++)
// 		{
//             // Determine the color based on the map value
//             if (map[y * mapX + x] == 1)
//                 color = HEX_WHITE;
//             else
//                 color = HEX_BLACK;

//             // Calculate the top-left corner of the square
//             xo = x * mapS;
//             yo = y * mapS;

//             // Draw a square of size squareSize x squareSize
//             for (yi = 0; yi < squareSize; yi++) {
//                 for (xi = 0; xi < squareSize; xi++) {
//                     draw_pixel(img, xo + xi, yo + yi, color);
//                 }
//             }
//         }
//     }
// }
