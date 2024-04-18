/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_radar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:03:48 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/18 01:34:10 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	t.base_center.x = (t.left.x + t.right.x) / 2;
	t.base_center.y = (t.left.y + t.right.y) / 2;

	return (t);
}

void	draw_player(mlx_image_t *img, t_player *player, t_point radar_center)
{
	t_triangle	t;
	int			thickness = 8; //change to test effect (1 is minimum and PLAYER_SIZE -1 is max)
	
	t = init_player_icon(player, radar_center);

	draw_line(img, t.base_center, t.front, HEX_GREEN);	
	// draw_triangle(img, &t, player->color);
	// draw_full_triangle(img, &t, player->color);
	draw_full_triangle_hollow(img, &t, thickness, player->color);
}

/* ************************************************************************** */

typedef struct s_radar
{
	mlx_image_t	*img;
	t_fpoint	player_pos;
	t_fpoint	map_center_offset;
	t_fpoint	player_minimap;
	t_point		radar_center;
	int			radius;
	t_fpoint	visible_top_left;
}				t_radar;

static t_radar	init_radar(t_minimap *mini)
{
	t_cub	*cub;
	t_map	*map;
	t_radar	r;

	cub = call_cub();
	map = get_map(cub->current_level);
	
	r.img = cub->radar_img;
	r.player_pos = cub->player.position;
	r.map_center_offset.x = (mini->img->width - map->width * mini->tile_size) / 2;
	r.map_center_offset.y = (mini->img->height - map->height * mini->tile_size) / 2;
	r.player_minimap.x = round(r.player_pos.x * mini->tile_size) + r.map_center_offset.x;
	r.player_minimap.y = round(r.player_pos.y * mini->tile_size) + r.map_center_offset.y;
	r.radar_center.x = r.img->width / 2;
	r.radar_center.y = r.img->height / 2;
	r.radius = ft_min(r.img->width, r.img->height) / 2;
	r.visible_top_left.x = r.player_minimap.x - r.radar_center.x;
	r.visible_top_left.y = r.player_minimap.y - r.radar_center.y;
	r.visible_top_left.x = ft_clamp(r.visible_top_left.x, 0, mini->img->width - r.img->width);
	r.visible_top_left.y = ft_clamp(r.visible_top_left.y, 0, mini->img->height - r.img->height);

	return (r);
}

static void	draw_visible_minimap(t_minimap *mini, t_radar r)
{
	int		y;
	int		x;
	t_point	map_pixel;
	int		color;

	y = 0;
	while (y < (int)r.img->height)
	{
		x = 0;
		while (x < (int)r.img->width)
		{
			map_pixel.x = r.visible_top_left.x + x;
			map_pixel.y = r.visible_top_left.y + y;
			if (is_in_circle((t_point){x, y}, (t_point){r.radar_center.x, r.radar_center.y}, r.radius - 100))
			{
				color = get_pixel(mini->img, map_pixel.x, map_pixel.y);
				draw_pixel(r.img, x, y, color);
			}
			x++;
		}
		y++;
	}
}

void	draw_radar(t_minimap *mini)
{
	t_radar		radar;
	t_player	*player;

	radar = init_radar(mini);
	player = &call_cub()->player;
	clear_img(radar.img);
	draw_visible_minimap(mini, radar);
	draw_player(radar.img, player, radar.radar_center);
	
	// draw_circle_hollow(radar.img, (t_fpoint){radar.radar_center.x, radar.radar_center.y}, 10, 2, HEX_BLUE);
	// draw_circle(radar.img, (t_fpoint){radar.radar_center.x, radar.radar_center.y}, 10, HEX_BLUE);
}
