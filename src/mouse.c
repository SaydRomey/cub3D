/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:09:30 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/18 08:47:07 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int get_color(int next)
// {
// 	static int colors[8] = {0xFFFFFF, 0x0000FF, 0x00FF00, 0xFF0000, 0x00FFFF, 0xFF00FF, 0xFFFF00, 0x000000};
// 	static int count = 0;

// 	if (next)
// 		count = (count + 1) % 8;
// 	return colors[count];
// }

int follow_mouse(int mouse_x, int mouse_y, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	// 
	draw_circle(&(cub->img), (t_point){mouse_x, mouse_y}, 10, HEX_BLUE);
	return (0);
}


// 

// mlx_key_hook (win->win_ptr, read_keys, img);
// mlx_hook(win->win_ptr, 2, 1L<<0, continuous_read_keys, img);
// mlx_mouse_hook (win->win_ptr, read_mouse, img);
// mlx_hook(win->win_ptr, 17, 1L<<0, exit_tutorial, img);
// mlx_hook(win->win_ptr, 6, 1L<<0, follow_mouse, img);

// int size = 10;
// int follow = 0;

// int follow_mouse(int mouse_x, int mouse_y, void *param)
// {
// 	int 		x;
// 	int 		y;
// 	t_cub 		*cub;

// 	cub = (t_cub *)param;
// 	if (!cub)
// 		return (1);
// 	if (mouse_x < 0 || mouse_y < 0 || mouse_x > WIDTH || mouse_y > HEIGHT)
// 		return (2);
// 	if (!follow)
// 		return (3);
// 	x = ((mouse_x % WIDTH) / size) * size;
// 	y = ((mouse_y % HEIGHT) / size) * size;
// 	draw_circle(&(cub->img), (t_point){x, y}, 10, HEX_BLUE);
// 	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img_ptr, 0, 0);
// 	return (0);
// }

// int read_mouse(int button, int mouse_x, int mouse_y, void *param)
// {
// 	int 		x;
// 	int 		y;
// 	t_cub 		*cub;

// 	cub = (t_cub *)param;
// 	if (!cub)
// 		return (-1);
// 	if (mouse_x < 0 || mouse_y < 0 || mouse_x > WIDTH || mouse_y > HEIGHT)
// 		return (2);
// 	x = ((mouse_x % WIDTH) / size) * size;
// 	y = ((mouse_y % HEIGHT) / size) * size;
// 	draw_circle(&(cub->img), (t_point){x, y}, 10, HEX_BLUE);
// 	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img_ptr, 0, 0);
// 	(void)button;
// 	return (0);
// }
