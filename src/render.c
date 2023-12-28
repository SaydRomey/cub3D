/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:13:16 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/23 22:13:55 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_horizon_line(t_img *img, t_point horizon, int color)
{
	draw_line(img, horizon, (t_point){WIDTH - 40, horizon.y}, color);
}

void	render(t_cub *cub)
{
	t_img	*img;

	img = &cub->img;
	clear_image(img);
	color_background(img, &cub->map);

	draw_mini_map(img, &cub->map); //maybe this could be done conditionnaly, not each frame ?
	draw_player(img, &cub->player);
	draw_cursor(img, cub);

	draw_horizon_line(img, cub->map.horizon, HEX_ORANGE);

	cub->prev_cursor = cub->cursor;
	
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img_ptr, 0, 0);
}
