/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 04:57:05 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/17 13:03:28 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"





// static t_point	find_center(t_minimap *mini, t_map *map)
// {
// 	(void)mini;
// 	(void)map;
	
// 	t_fpoint	pos = call_cub()->player.position;
// 	t_point		center;

// 	center.x = pos.x;
// 	center.y = pos.y;
// 	return center;
// }

// static void	calculate_bounds(t_point center, t_point *start, t_point *end, t_minimap *mini, t_map *map)
// {
// 	int			half_width = mini->img->width / (2 * mini->tile_size);
// 	int			half_height = mini->img->height / (2 * mini->tile_size);

// 	start->x = ft_max(0, center.x - half_width);
// 	start->y = ft_max(0, center.y - half_height);
// 	end->x = ft_min(map->width, center.x + half_width);
// 	end->y = ft_min(map->height, center.y + half_height);
// }



// static void make_it_round(t_minimap *mini, t_map *map)
// {
// 	(void)map;
	
//     int radius = mini->radius;
//     t_point circle_center = {mini->round_img->width / 2, mini->round_img->height / 2};

//     t_fpoint pos = call_cub()->player.position;
//     // Convert player's map position to pixel coordinates on the minimap
//     int player_minimap_x = pos.x * mini->tile_size;
//     int player_minimap_y = pos.y * mini->tile_size;

//     // Calculate the top-left corner of the square that will be visible in the round minimap
//     int visible_top_left_x = player_minimap_x - radius;
//     int visible_top_left_y = player_minimap_y - radius;

//     // Clamp these values to ensure they are within the bounds of the full minimap
//     visible_top_left_x = ft_clamp(visible_top_left_x, 0, mini->img->width - mini->round_img->width);
//     visible_top_left_y = ft_clamp(visible_top_left_y, 0, mini->img->height - mini->round_img->height);

//     for (int y = 0; y < (int)mini->round_img->height; y++) {
//         for (int x = 0; x < (int)mini->round_img->width; x++) {
//             // Calculate the actual pixel positions on the full minimap
//             int map_x = visible_top_left_x + x;
//             int map_y = visible_top_left_y + y;

//             // Check if this pixel is within the circular radius of the player's position
//             if (is_in_circle((t_point){x, y}, circle_center, radius))
// 			{
//                 // If it is, copy the pixel from the full minimap to the round minimap
//                 int color = get_pixel(mini->img, map_x, map_y);
//                 draw_pixel(mini->round_img, x, y, color);
//             }
// 			// else
// 			// {
//             //     // Optionally clear or set a specific color for pixels outside the radius
//             //     // draw_pixel(mini->round_img, x, y, BACKGROUND_COLOR); // Define BACKGROUND_COLOR as needed
//             // }
//         }
//     }
// }


// static void	make_it_round(t_minimap *mini, t_map *map)
// {
// 	int		radius = mini->round_img->width / 3;
// 	t_point	circle_center = {radius, radius};

// 	int	map_width = map->width * mini->tile_size;
// 	int	map_height = map->height * mini->tile_size;

// 	t_fpoint	pos = call_cub()->player.position;

// 	int	center_offset_x = (int)pos.x - radius;
// 	int	center_offset_y = (int)pos.y - radius;

// 	center_offset_x = ft_clamp(center_offset_x, 0, map_width - mini->round_img->width);
// 	center_offset_y = ft_clamp(center_offset_y, 0, map_height - mini->round_img->height);

// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < (int)mini->round_img->height)
// 	{
// 		x = 0;
// 		while (x < (int)mini->round_img->width)
// 		{
// 			if (is_in_circle((t_point){x, y}, circle_center, radius))
// 			{
// 				int	map_x = center_offset_x + x;
// 				int	map_y = center_offset_y + y;

// 				int	color = get_pixel(mini->img, map_x, map_y);
// 				draw_pixel(mini->round_img, x, y, color);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	draw_minimap(t_minimap *mini, t_map *map)
// {
// 	t_point	start, end;

// 	clear_img(mini->img);
// 	clear_img(mini->round_img);

// 	t_point center = find_center(mini, map);
// 	calculate_bounds(center, &start, &end, mini, map);
// 	draw_tiles(mini, start, end);
// 	// make_it_round(mini, map);
// 	// move_img(mini->round_img, 500, 500);
// }


