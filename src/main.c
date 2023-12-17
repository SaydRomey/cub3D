/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:24:06 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/16 20:57:29 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
initializes mlx, window, image elements of t_cub
*/
static t_cub	init_cub(char *path)
{
	t_cub	cub;
	char	*title;

	proof("Initiating mlx");
	title = ft_strjoin("cub3D - ", path);
	ft_memset(&cub, 0, sizeof(cub));
	cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, WIDTH, HEIGHT, title);
	free(title);
	cub.img.img_ptr = mlx_new_image(cub.mlx_ptr, WIDTH, HEIGHT);
	cub.img.addr = mlx_get_data_addr(cub.img.img_ptr, &cub.img.bpp,
			&cub.img.line_length, &cub.img.endian);
	return (cub);
}

static void	cub_loop(t_cub *cub)
{
	mlx_hook(cub->win_ptr, KEY_PRESS, KEY_PRESS_MASK, key_press, cub);
    mlx_hook(cub->win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, key_release, cub);
    mlx_hook(cub->win_ptr, DESTROY, 0, terminate_mlx, cub);
	
// print keys in terminal (interferes with the loop hook)
	// mlx_key_hook(cub->win_ptr, key_print, cub);

// Set the loop hook for continuous updates
    mlx_loop_hook(cub->mlx_ptr, update_game, cub);

// main loop
	mlx_loop(cub->mlx_ptr);
}

int	main(void)
{
	t_cub		cub;
	t_point		start = {100, 100};

	cub = init_cub("[map title]");
	cub.player = init_player(start);
	cub.map = init_map();
	cub_loop(&cub);
	terminate_mlx(&cub);
	return (0);
}
