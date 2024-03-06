/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/06 16:45:01 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub	init_cub(char *filepath)
{
	t_cub	cub;
	char	*title;

	ft_memset(&cub, 0, sizeof(t_cub));
	title = ft_strjoin("cub3D - ", filepath);
	cub.mlx = mlx_init(WIDTH, HEIGHT, title, FALSE);
	free(title);
	if (!cub.mlx)
		error_mlx();
	// 
	cub.img = mlx_new_image(cub.mlx, WIDTH, HEIGHT);
	if (!cub.img)
		error();
	// 
	proof("init ok");
	return (cub);
}

void	setup_images(t_cub *cub)
{
	// cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	// if (!cub->img)
	// 	error_mlx();
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) < SUCCESS)
		error_mlx();
	// cub->img->instances->enabled = false; //tmp
	// 
	cub->texture[NO] = load_png("img/bluestone.png", cub->mlx);
	cub->texture[SO] = load_png("img/eagle.png", cub->mlx);
	cub->texture[EA] = load_png("img/redbrick.png", cub->mlx);
	cub->texture[WE] = load_png("img/wood.png", cub->mlx);
	cub->texture[F] = load_png("img/wood.png", cub->mlx);
	cub->texture[C] = load_png("img/pikachu.png", cub->mlx);
	cub->texture[I] = load_png("img/pokeball.png", cub->mlx);
	// 
}

/*
hooks and loops
*/
void	cub_loop(t_cub *cub)
{
	set_mouse(cub);
	mlx_key_hook(cub->mlx, &keyhooks, cub);
	mlx_loop_hook(cub->mlx, update, cub);
	
	mlx_loop(cub->mlx);
}


int	main(int argc, char **argv)
{
	t_scene	scene;
	t_cub	cub;

	validate_arguments(argc, argv);
	scene = parse_cubfile(argv[1]);

	cub = init_cub(argv[1]);
	
	cub.map = init_map(&scene);

	ft_printf("Width %d\n", cub.map.width);
	ft_printf("Height %d\n", cub.map.height);
	// cub.player = init_player(&scene);
	cub.player = init_player((t_fpoint){8, 2}, 'S');
	
	cleanup_scene(&scene); //all info should be transfered to the map

	// cub.raycast = ...

	setup_images(&cub);
	cub_loop(&cub);
	cleanup(&cub);

	return (SUCCESS);
}

// t_cub	*call_cub(void)
// {
// 	static t_cub	*scub;

// 	if 
// }

// call_cub()->

// call_map()->