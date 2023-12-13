/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:24:06 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/12 20:01:58 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_mlx *cub3d)
{
	clear_image(&(cub3d->img));
	draw_pixel(&(cub3d->img), 50, 50, HEX_YELLOW);
	draw_pixel(&(cub3d->img), 55, 55, HEX_RED);
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr, cub3d->img.img_ptr, 0, 0);
}

int	terminate_mlx(t_mlx *cub3d)
{
	safe_free((void **)&cub3d->mlx_ptr);
	exit(SUCCESS);
}

// 

/*
initializes mlx, window, image elements of t_mlx (t_cub)
*/
static t_mlx	init_cub3d(char *str)
{
	t_mlx	cub3d;
	char	*title;

	title = ft_strjoin("cub3D - ", str);
	cub3d.mlx_ptr = mlx_init();
	cub3d.win_ptr = mlx_new_window(cub3d.mlx_ptr, WIDTH, HEIGHT, title);
	safe_free((void **)&title);
	cub3d.img.img_ptr = mlx_new_image(cub3d.mlx_ptr, WIDTH, HEIGHT);
	cub3d.img.addr = mlx_get_data_addr(cub3d.img.img_ptr, &cub3d.img.bpp,
		&cub3d.img.line_length, &cub3d.img.endian);
	return (cub3d);
}

/* 
handles first rendering, sets the hooks, then loops the mlx
*/
static void	cub3d_loop(t_mlx *cub3d)
{
	render(cub3d);
	// mlx_key_hook(cub3d->win_ptr, key_input, cub3d);
	mlx_hook(cub3d->win_ptr, 0, 0, terminate_mlx, cub3d);
	mlx_loop(cub3d->mlx_ptr);
}

int	main(void)
{
	t_mlx	cub3d;

	cub3d = init_cub3d("Title");
	cub3d_loop(&cub3d);
	
	

	// terminate_mlx(&cub3d);
	return (0);
}
