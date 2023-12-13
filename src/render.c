/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:13:16 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/13 15:20:05 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_test(t_img *img)
{
	t_point	start = {200, 200};
	t_point	end = {400, 400};

	draw_line(img, start, end, HEX_ORANGE);
	
	draw_pixel(img, 50, 50, HEX_GREEN);
	draw_pixel(img, 150, 150, HEX_YELLOW);
	
}

void	render(t_cub *cub)
{
	proof("Rendering");
	clear_image(&(cub->img));
	// 
	pixel_test(&(cub->img));
	// 
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img_ptr, 0, 0);
	// if (cub->param.toggle.menu == ON)
	// 	display_menu(cub);
	// else
	// 	cub_text(cub, "(H)elp", MENU_X, MENU_Y);
}
