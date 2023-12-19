/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:13:16 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/19 14:55:57 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_horizon_line(t_img *img, t_point horizon, int color)
{
	draw_line(img, horizon, (t_point){WIDTH - 40, horizon.y}, color);
}

void	render(t_cub *cub)
{
	// t_img	*img;

	// img = &cub->img;
	clear_image(&cub->img);
	color_background(&cub->img, cub->map.floor_color, cub->map.ceiling_color);

	draw_mini_map(&cub->img, &cub->map);
	draw_player(&cub->img, &cub->player);
	draw_cursor(&cub->img, cub);

	draw_horizon_line(&cub->img, cub->horizon, HEX_ORANGE);

	cub->prev_cursor = cub->cursor;
	
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img_ptr, 0, 0);
}
