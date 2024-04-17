// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   raycast_assets.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/21 13:04:20 by oroy              #+#    #+#             */
// /*   Updated: 2024/03/29 16:29:45 by oroy             ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "cub3d.h"

static void	sort_sprites(t_asset *sprite)
{
	t_asset	tmp;
	int		swap_times;
	int		i;

	swap_times = NUMSPRITES - 1;
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

static void	set_sprite_distance(t_asset *s)
{
	t_fpoint	player;
	t_fpoint	sprite;
	int			i;

	i = 0;
	player = call_cub()->player.position;
	while (i < NUMSPRITES)
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
	int			d;
	int			color;
	t_point		tex;

	x = s.h.start;
	while (x < s.h.end)
	{
		tex.x = (int)(256 * (x - (s.screen_x - s.h.size / 2)) * s.tex->width / s.h.size) / 256;
		if (s.transform.y > 0 && x >= 0 && x < WIDTH && s.transform.y < z_buffer[x])
		{
			y = s.v.start;
			while (y < s.v.end)
			{
				d = y * 256 - HEIGHT * 128 + s.v.size * 128;
				tex.y = d * s.tex->height / s.v.size / 256;
				color = get_pixel(s.tex, tex.x, tex.y);
				if (get_alpha(color) == 255)
					draw_pixel(cub->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}

void	draw_assets(t_cub *cub, float z_buffer[WIDTH])
{
	t_asset		*s;
	float		inv_det;
	int			i;

	s = get_level(cub->current_level)->assets;
	set_sprite_distance(s);
	sort_sprites(s);
	//
	i = 0;
	while (i < NUMSPRITES)
	{
		inv_det = 1.0 / (cub->player.cam_plane.x * cub->player.delta.y - cub->player.delta.x * cub->player.cam_plane.y);
		s[i].transform.x = inv_det * (cub->player.delta.y * s[i].pos_relative.x - cub->player.delta.x * s[i].pos_relative.y);
		s[i].transform.y = inv_det * (-cub->player.cam_plane.y * s[i].pos_relative.x + cub->player.cam_plane.x * s[i].pos_relative.y);
		s[i].screen_x = (int)((WIDTH / 2) * (1 + s[i].transform.x / s[i].transform.y));

		// Calculate dimensions
		s[i].v = get_stripe_data(s[i].transform.y, HEIGHT / 2, HEIGHT);
		s[i].h = get_stripe_data(s[i].transform.y, s[i].screen_x, WIDTH);

		// Loop through all vertical stripes of the sprites
		draw_asset_pixels(cub, s[i], z_buffer);
		
		i++;
	}
}


// void	draw_assets(t_cub *cub, float z_buffer[WIDTH])
// {
// 	t_asset		*s;
// 	int			i;
// 	int			x;
// 	int			y;
// 	int			d;
// 	int			color;
// 	int			screen_x;
// 	float		inv_det;
// 	t_point		tex;
// 	t_point		sprite_dimensions;
// 	t_point		draw_start;
// 	t_point		draw_end;
// 	// t_fpoint	pos_relative;
// 	t_fpoint	transform;
// 	t_line		h;
// 	t_line		v;

// 	s = get_level(cub->current_level)->assets;
// 	set_sprite_distance(s);
// 	sort_sprites(s);
// 	//
// 	i = 0;
// 	while (i < NUMSPRITES)
// 	{
// 		// pos_relative.x = sprite[i].position.x - pos.x;
// 		// pos_relative.y = sprite[i].position.y - pos.y;
// 		inv_det = 1.0 / (cub->player.cam_plane.x * cub->player.delta.y - cub->player.delta.x * cub->player.cam_plane.y);
// 		transform.x = inv_det * (cub->player.delta.y * s[i].pos_relative.x - cub->player.delta.x * s[i].pos_relative.y);
// 		transform.y = inv_det * (-cub->player.cam_plane.y * s[i].pos_relative.x + cub->player.cam_plane.x * s[i].pos_relative.y);
// 		screen_x = (int)((WIDTH / 2) * (1 + transform.x / transform.y));
// 		// Calculate Height
// 		sprite_dimensions.y = ft_abs((int)(HEIGHT / transform.y));
// 		draw_start.y = HEIGHT / 2 - sprite_dimensions.y / 2;
// 		if (draw_start.y < 0)
// 			draw_start.y = 0;
// 		draw_end.y = HEIGHT / 2 + sprite_dimensions.y / 2;
// 		if (draw_end.y >= HEIGHT)
// 			draw_end.y = HEIGHT - 1;

// 		v = get_stripe_data(transform.y, HEIGHT / 2, HEIGHT);
// 		h = get_stripe_data(transform.y, screen_x, WIDTH);
// 		// Calculate Width
// 		sprite_dimensions.x = ft_abs((int)(HEIGHT / transform.y));
// 		draw_start.x = screen_x - sprite_dimensions.x / 2;
// 		if (draw_start.x < 0)
// 			draw_start.x = 0;
// 		draw_end.x = screen_x + sprite_dimensions.x / 2;
// 		if (draw_end.x >= WIDTH)
// 			draw_end.x = WIDTH - 1;
// 		// Loop through all vertical stripes of the sprites
// 		x = draw_start.x;
// 		while (x < draw_end.x)
// 		{
// 			tex.x = (int)(256 * (x - (screen_x - h.size / 2)) * cub->texture[J]->width / h.size) / 256;
// 			if (transform.y > 0 && x >= 0 && x < WIDTH && transform.y < z_buffer[x])
// 			{
// 				y = draw_start.y;
// 				while (y < draw_end.y)
// 				{
// 					d = y * 256 - HEIGHT * 128 + v.size * 128;
// 					tex.y = d * cub->texture[J]->height / v.size / 256;
// 					color = get_pixel(cub->texture[J], tex.x, tex.y);
// 					if (get_alpha(color) == 255)
// 						draw_pixel(cub->img, x, y, color);
// 					y++;
// 				}
// 			}
// 			x++;
// 		}
// 		i++;
// 	}
// }
