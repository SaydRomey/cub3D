/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_assets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:12:06 by oroy              #+#    #+#             */
/*   Updated: 2024/04/26 16:44:17 by olivierroy       ###   ########.fr       */
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

static void	draw_asset_pixels(t_cub *cub, t_asset s, float z_buffer[WIDTH])
{
	int			x;
	int			y;
	int			start_pos;
	int			color;
	t_point		tex;

	x = s.h.start;
	while (x < s.h.end)
	{
		tex.x = ft_abs(x - (s.screen_x - s.h.size / 2)) * s.tex->width / s.h.size;
		if (s.transform.y > 0 && x >= 0 && x < WIDTH && s.transform.y < z_buffer[x])
		{
			y = s.v.start;
			while (y < s.v.end)
			{
				start_pos = ft_abs(y - HEIGHT / 2 + s.v.size / 2);
				tex.y = start_pos * s.tex->height / s.v.size;
				color = get_pixel(s.tex, tex.x, tex.y);
				if (get_alpha(color) == 255)
					draw_pixel(cub->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}

static void	start_drawing_assets(t_cub *cub, float z_buffer[WIDTH])
{
	t_asset		*s;
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
		s[i].transform.x = inv * rot_matrix(s[i].pos_relative, cub->player.delta);
		s[i].transform.y = inv * rot_matrix(cub->player.cam_plane, s[i].pos_relative);
		s[i].screen_x = (int)((WIDTH / 2) * (1 + s[i].transform.x / s[i].transform.y));
		s[i].v = get_stripe_data(s[i].transform.y, HEIGHT / 2, HEIGHT);
		s[i].h = get_stripe_data(s[i].transform.y, s[i].screen_x, WIDTH);
		draw_asset_pixels(cub, s[i], z_buffer);
		i++;
	}
}

void	draw_assets(t_cub *cub)
{
	if (get_level(cub->current_level)->assets)
		start_drawing_assets(cub, cub->raycast.z_buffer);
}
