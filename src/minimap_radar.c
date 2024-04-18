/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_radar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:03:48 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/17 19:50:55 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	draw_player(mlx_image_t *img, t_player *player, t_point radar_center)
// {
// 	t_fpoint	front;
// 	t_fpoint	left;
// 	t_fpoint	right;
// 	t_fpoint	base_center;
// 	float		half_base;

// 	half_base = player->size * tan(degree_to_radian(30));

// 	// Front vertex of the triangle
// 	front.x = radar_center.x + player->delta.x * player->size;
// 	front.y = radar_center.y + player->delta.y * player->size;

// 	// Left and right vertices
// 	left.x = radar_center.x - player->delta.y * half_base;
// 	left.y = radar_center.y + player->delta.x * half_base;
// 	right.x = radar_center.x + player->delta.y * half_base;
// 	right.y = radar_center.y - player->delta.x * half_base;

// 	// Calculating the midpoint of the base
// 	base_center.x = (left.x + right.x) / 2;
// 	base_center.y = (left.y + right.y) / 2;

// 	draw_triangle(img, front, left, right, player->color);
// 	draw_line(img, base_center, front, HEX_MAGENTA);
// }

t_triangle	init_player_icon(t_player *player, t_point radar_center)
{
	t_triangle	t;
	
	t.half_base = player->size * tan(degree_to_radian(30));
	t.height = player->size * (sqrt(3) / 2);

	t.centroid.x = radar_center.x - player->delta.x * (t.height / 3);
	t.centroid.y = radar_center.y - player->delta.y * (t.height / 3);

	t.front.x = t.centroid.x + player->delta.x * player->size;
	t.front.y = t.centroid.y + player->delta.y * player->size;
	t.left.x = t.centroid.x - player->delta.y * t.half_base;
	t.left.y = t.centroid.y + player->delta.x * t.half_base;
	t.right.x = t.centroid.x + player->delta.y * t.half_base;
	t.right.y = t.centroid.y - player->delta.x * t.half_base;

	return (t);
}

void	draw_player(mlx_image_t *img, t_player *player, t_point radar_center)
{
	t_triangle	t;
	
	t = init_player_icon(player, radar_center);
	// draw_triangle(img, &t, player->color);
	draw_full_triangle(img, &t, player->color);
	
}
void draw_radar(t_minimap *mini)
{
	mlx_image_t	*radar = call_cub()->radar_img;
	
	t_map	*map = get_map(call_cub()->current_level);
	t_fpoint player_pos = call_cub()->player.position;
	
	// Calculate the minimap centering offset due to non-square dimensions
	int map_width_pixels = map->width * mini->tile_size;
	int map_height_pixels = map->height * mini->tile_size;
	int map_center_offset_x = (mini->img->width - map_width_pixels) / 2;
	int map_center_offset_y = (mini->img->height - map_height_pixels) / 2;

	// Convert player's map position to pixel coordinates on the minimap with center offset
	t_point	player_minimap;
	player_minimap.x = round(player_pos.x * mini->tile_size) + map_center_offset_x;
	player_minimap.y = round(player_pos.y * mini->tile_size) + map_center_offset_y;

	// Radar center should match player's position
	int radar_center_x = radar->width / 2;
	int radar_center_y = radar->height / 2;
	int radius = ft_min(radar->width, radar->height) / 2;

	// Calculate the top-left corner of the area to be displayed in the radar
	t_point	visible_top_left;
	visible_top_left.x = player_minimap.x - radar_center_x;
	visible_top_left.y = player_minimap.y - radar_center_y;

	// Clamp these values to ensure they are within the bounds of the full minimap
	visible_top_left.x = ft_clamp(visible_top_left.x, 0, mini->img->width - radar->width);
	visible_top_left.y = ft_clamp(visible_top_left.y, 0, mini->img->height - radar->height);
	
	clear_img(radar);

	// Draw the visible part of the minimap onto the radar
	int		y;
	int		x;
	t_point	map_pixel;
	int		color;

	y = 0;
	while (y < (int)radar->height)
	{
		x = 0;
		while (x < (int)radar->width)
		{
			map_pixel.x = visible_top_left.x + x;
			map_pixel.y = visible_top_left.y + y;
			if (is_in_circle((t_point){x, y}, (t_point){radar_center_x, radar_center_y}, radius - 100))
			{
				color = get_pixel(mini->img, map_pixel.x, map_pixel.y);
				draw_pixel(radar, x, y, color);
			}
			x++;
		}
		y++;
	}
	draw_player(radar, &call_cub()->player, (t_point){radar_center_x, radar_center_y});
	// draw_circle_hollow(radar, (t_fpoint){radar_center_x, radar_center_y}, 12, 5, HEX_GREEN);
}

/* ************************************************************************** */
/* ************************************************************************** */

// typedef struct s_radar
// {
// 	mlx_image_t	*img;
// 	t_point		player_minimap;
// 	t_point		top_left;
// 	t_point		center;
// 	t_minimap	*mini;
// 	int			radius;
// }				t_radar;
