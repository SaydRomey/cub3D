/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_assets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:04:20 by oroy              #+#    #+#             */
/*   Updated: 2024/03/29 16:29:45 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_asset	*init_assets(void)
{
	t_asset	*assets;

	assets = ft_calloc(NUMSPRITES, sizeof (t_asset));
	if (!assets)
		return (NULL);
	assets[0].position = (t_fpoint){6.5, 5.5};
	assets[1].position = (t_fpoint){6.5, 4.5};
	return (assets);
}

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

void	draw_assets(t_cub *cub, float z_buffer[WIDTH])
{
	int			i;
	int			x;
	int			y;
	int			d;
	int			color;
	int			sprite_screen_x;
	float		inv_det;
	t_point		tex;
	t_point		sprite_dimensions;
	t_point		draw_start;
	t_point		draw_end;
	t_fpoint	pos;
	t_fpoint	pos_relative;
	t_fpoint	transform;
	t_asset		*sprite;

	i = 0;
	sprite = cub->assets;
	pos = cub->player.position;
	while (i < NUMSPRITES)
	{
		sprite[i].distance = ((pos.x - sprite[i].position.x) * (pos.x - sprite[i].position.x) + (pos.y - sprite[i].position.y) * (pos.y - sprite[i].position.y));
		i++;
	}
	sort_sprites(sprite);
	//
	i = 0;
	while (i < NUMSPRITES)
	{
		pos_relative.x = sprite[i].position.x - pos.x;
		pos_relative.y = sprite[i].position.y - pos.y;
		inv_det = 1.0 / (cub->player.cam_plane.x * cub->player.delta.y - cub->player.delta.x * cub->player.cam_plane.y);
		transform.x = inv_det * (cub->player.delta.y * pos_relative.x - cub->player.delta.x * pos_relative.y);
		transform.y = inv_det * (-cub->player.cam_plane.y * pos_relative.x + cub->player.cam_plane.x * pos_relative.y);
		sprite_screen_x = (int)((WIDTH / 2) * (1 + transform.x / transform.y));
		// Calculate Height
		sprite_dimensions.y = ft_abs((int)(HEIGHT / transform.y));
		draw_start.y = HEIGHT / 2 - sprite_dimensions.y / 2;
		if (draw_start.y < 0)
			draw_start.y = 0;
		draw_end.y = HEIGHT / 2 + sprite_dimensions.y / 2;
		if (draw_end.y >= HEIGHT)
			draw_end.y = HEIGHT - 1;
		// Calculate Width
		sprite_dimensions.x = ft_abs((int)(HEIGHT / transform.y));
		draw_start.x = sprite_screen_x - sprite_dimensions.x / 2;
		if (draw_start.x < 0)
			draw_start.x = 0;
		draw_end.x = sprite_screen_x + sprite_dimensions.x / 2;
		if (draw_end.x >= WIDTH)
			draw_end.x = WIDTH - 1;
		// Loop through all vertical stripes of the sprites
		x = draw_start.x;
		while (x < draw_end.x)
		{
			tex.x = (int)(256 * (x - (sprite_screen_x - sprite_dimensions.x / 2)) * cub->texture[J]->width / sprite_dimensions.x) / 256;
			if (transform.y > 0 && x >= 0 && x < WIDTH && transform.y < z_buffer[x])
			{
				y = draw_start.y;
				while (y < draw_end.y)
				{
					d = y * 256 - HEIGHT * 128 + sprite_dimensions.y * 128;
					tex.y = d * cub->texture[J]->height / sprite_dimensions.y / 256;
					color = get_pixel(cub->texture[J], tex.x, tex.y);
					if (color & 0xFF)
						draw_pixel(cub->img, x, y, color);
					y++;
				}
			}
			x++;
		}
		i++;
	}
}
