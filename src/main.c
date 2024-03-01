/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/29 21:54:48 by cdumais          ###   ########.fr       */
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
		error();
	return (cub);
}

void	setup_images(t_cub *cub)
{
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		error();
	cub->minimap_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT); //to change later?
	if (!cub->minimap_img)
		error();
	// 
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) < SUCCESS)
		error();
	cub->img->instances->enabled = false; //tmp
	if (mlx_image_to_window(cub->mlx, cub->minimap_img, 0, 0) < SUCCESS)
		error();
	// cub->minimap_img.instance.enabled = false; //tmp
}

/*
hooks and loops
*/
void	cub_loop(t_cub *cub)
{
	mlx_key_hook(cub->mlx, &keyhooks, cub);
	mlx_loop_hook(cub->mlx, update, cub);
	
	mlx_loop(cub->mlx);
}

/* ************************************************************************** */

static void	validate_arguments(int argc, char **argv)
{
	int		check;
	char	*extension;

	if (argc != 2)
		va_exit_error("Usage: %s <filename>.cub", argv[0]);

	// check for valid extension
	extension = ft_strrchr(argv[1], '.');
	if (!extension || ft_strrncmp(extension, ".cub", 4) != SAME)
		va_exit_error("Invalid file extension");

	// validate file (exists and is not empty)
	check = read_check(argv[1]);
	if (check == 0)
		va_exit_error("Error: file is empty: %s", argv[1]);
	else if (check == -1)
		va_exit_error("Error: could not open or read: %s", argv[1]);
	ft_printf("Args are valid\n");
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	t_scene	scene;

	validate_arguments(argc, argv);
	scene = parse_cubfile(argv[1]);
	// &scene.next = parse_cubfile("./map/lvl2.cub");
	// validate_scene(&scene);

	cub = init_cub(argv[1]);
	cub.minimap = init_map(&scene);
	cub.player = init_player((t_point){100,100}, 'S');

	setup_images(&cub);
	
	ft_printf("\nTexture paths:\n");
	ft_printf("North: %s\n", scene.wall_textures[NO]);
	ft_printf("South: %s\n", scene.wall_textures[SO]);
	ft_printf("East: %s\n", scene.wall_textures[EA]);
	ft_printf("West: %s\n", scene.wall_textures[WE]);
	// 
	ft_printf("\nFloor and Ceiling colors:\n");
	ft_printf("RED:   %s\n", scene.colors[FLOOR][R]);
	ft_printf("GREEN: %s\n", scene.colors[FLOOR][G]);
	ft_printf("BLUE:  %s\n", scene.colors[FLOOR][B]);
	scene.floor = get_color(&scene, FLOOR);
	ft_printf("Hexa value: %X\n", scene.floor);

	ft_printf("\nCeiling colors:\n");
	ft_printf("RED:   %s\n", scene.colors[CEILING][R]);
	ft_printf("GREEN: %s\n", scene.colors[CEILING][G]);
	ft_printf("BLUE:  %s\n", scene.colors[CEILING][B]);
	scene.ceiling = get_color(&scene, CEILING);
	ft_printf("Hexa value: %X\n", scene.ceiling);

	cub_loop(&cub);
	cleanup(&cub);

	return (SUCCESS);
}

/*
	
	*/