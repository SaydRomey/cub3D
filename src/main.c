/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:24:06 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/13 15:17:06 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
initializes mlx, window, image elements of t_cub
*/
static t_cub	initiate_cub(char *path)
{
	t_cub	cub;
	char	*title;

	title = ft_strjoin("cub3D - ", path);
	proof("Initiating mlx");
	cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, WIDTH, HEIGHT, title);
	safe_free((void **)&title);
	cub.img.img_ptr = mlx_new_image(cub.mlx_ptr, WIDTH, HEIGHT);
	cub.img.addr = mlx_get_data_addr(cub.img.img_ptr, &cub.img.bpp,
			&cub.img.line_length, &cub.img.endian);
	return (cub);
}

/* 
handles first rendering, sets the hooks, then loops the mlx
*/
static void	cub_loop(t_cub *cub)
{
	render(cub);
	mlx_key_hook(cub->win_ptr, key_input, cub);
	mlx_hook(cub->win_ptr, DESTROY, 0, terminate_mlx, cub);
	mlx_loop(cub->mlx_ptr);
}


int	main(void)
{
	t_cub	cub;

	cub = initiate_cub("[map title]");
	cub_loop(&cub);
	terminate_mlx(&cub);
	return (0);
}
