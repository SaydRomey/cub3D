/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_assets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:12:06 by oroy              #+#    #+#             */
/*   Updated: 2024/04/29 18:58:25 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sort_sprites(t_asset *sprite, int total)
{
	t_asset	tmp;
	int		swap_times;
	int		i;

	swap_times = total - 1;
	while (swap_times)
	{
		i = 0;
		while (i < swap_times)
		{
			if (sprite[i].distance < sprite[i + 1].distance)
			{
				tmp = sprite[i];
				sprite[i] = sprite[i + 1];
				sprite[i + 1] = tmp;
			}
			i++;
		}
		swap_times--;
	}
}

static void	set_sprite_distance(t_asset *s, int total)
{
	t_fpoint	player;
	t_fpoint	sprite;
	int			i;

	i = 0;
	player = call_cub()->player.position;
	while (i < total)
	{
		sprite = s[i].pos;
		s[i].pos_relative.x = sprite.x - player.x;
		s[i].pos_relative.y = sprite.y - player.y;
		s[i].distance = s[i].pos_relative.x * s[i].pos_relative.x;
		s[i].distance += s[i].pos_relative.y * s[i].pos_relative.y;
		i++;
	}
}

static void	draw_asset_pixels(t_cub *cub, t_asset s, t_texture tex, float *z)
{
	int	x;
	int	y;

	x = s.h.start;
	tex.pos_x = (x - (s.screen_x - s.h.size / 2)) * tex.step_x;
	while (x < s.h.end)
	{
		tex.pixel.x = (int)tex.pos_x % tex.width;
		tex.pos_x += tex.step_x;
		if (s.tf.y > 0 && x >= 0 && x < WIDTH && s.tf.y < z[x])
		{
			y = s.v.start;
			tex.pos_y = (y - HEIGHT / 2 + s.v.size / 2) * tex.step_y;
			while (y < s.v.end)
			{
				tex.pixel.y = (int)tex.pos_y % tex.height;
				tex.pos_y += tex.step_y;
				asset_pixel(cub->img, x, y, \
				get_pixel(tex.to_draw, tex.pixel.x, tex.pixel.y));
				y++;
			}
		}
		x++;
	}
}

/**
 * Uses the inverse camera matrix to get the asset position
 * in camera space. Here, tf.y is actually the depth of the asset
 * (similar to the wall perpendicular distance)
*/
static void	start_drawing_assets(t_cub *cub)
{
	t_asset		*s;
	t_texture	tex;
	float		inv;
	int			total;
	int			i;

	total = get_level(cub->current_level)->assets_total;
	s = get_level(cub->current_level)->assets;
	set_sprite_distance(s, total);
	sort_sprites(s, total);
	i = 0;
	while (i < total)
	{
		inv = 1.0 / rot_matrix(cub->player.cam_plane, cub->player.delta);
		s[i].tf.x = inv * rot_matrix(s[i].pos_relative, cub->player.delta);
		s[i].tf.y = inv * rot_matrix(cub->player.cam_plane, s[i].pos_relative);
		s[i].screen_x = (int)((WIDTH / 2) * (1 + s[i].tf.x / s[i].tf.y));
		s[i].v = get_stripe_data(s[i].tf.y, HEIGHT / 2, HEIGHT);
		s[i].h = get_stripe_data(s[i].tf.y, s[i].screen_x, WIDTH);
		tex = get_texture_info(s[i].tex);
		tex.step_x = tex.width / (float)s[i].h.size;
		tex.step_y = tex.height / (float)s[i].v.size;
		draw_asset_pixels(cub, s[i], tex, cub->raycast.z_buffer);
		i++;
	}
}

void	draw_assets(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (get_level(cub->current_level)->assets)
		start_drawing_assets(cub);
}
