/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/04 22:21:26 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// t_cub	init_cub(char *filepath)
// {
// 	t_cub	cub;
// 	char	*title;

// 	ft_memset(&cub, 0, sizeof(t_cub));
// 	title = ft_strjoin("cub3D - ", filepath);
// 	cub.mlx = mlx_init(WIDTH, HEIGHT, title, FALSE);
// 	free(title);
// 	if (!cub.mlx)
// 		error();
// 	return (cub);
// }

// void	setup_images(t_cub *cub)
// {
// 	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
// 	if (!cub->img)
// 		error();
// 	cub->minimap_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT); //to change later?
// 	if (!cub->minimap_img)
// 		error();
// 	// 
// 	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) < SUCCESS)
// 		error();
// 	cub->img->instances->enabled = false; //tmp
// 	if (mlx_image_to_window(cub->mlx, cub->minimap_img, 0, 0) < SUCCESS)
// 		error();
// 	// cub->minimap_img.instance.enabled = false; //tmp
// }

/*
hooks and loops
*/
// void	cub_loop(t_cub *cub)
// {
// 	mlx_key_hook(cub->mlx, &keyhooks, cub);
// 	mlx_loop_hook(cub->mlx, update, cub);
	
// 	mlx_loop(cub->mlx);
// }

/* ************************************************************************** */

// static void	test_parsing(t_scene scene)
// {
// 	ft_printf("\nTexture paths:\n");
// 	ft_printf("North: %s\n", scene.wall_textures[NO]);
// 	ft_printf("South: %s\n", scene.wall_textures[SO]);
// 	ft_printf("East: %s\n", scene.wall_textures[EA]);
// 	ft_printf("West: %s\n", scene.wall_textures[WE]);
// 	// 
// 	ft_printf("\nFloor and Ceiling colors:\n");
// 	ft_printf("RED:   %s\n", scene.colors[FLOOR][R]);
// 	ft_printf("GREEN: %s\n", scene.colors[FLOOR][G]);
// 	ft_printf("BLUE:  %s\n", scene.colors[FLOOR][B]);
// 	scene.floor = get_color(&scene, FLOOR);
// 	ft_printf("Hexa value: %X\n", scene.floor);

// 	ft_printf("\nCeiling colors:\n");
// 	ft_printf("RED:   %s\n", scene.colors[CEILING][R]);
// 	ft_printf("GREEN: %s\n", scene.colors[CEILING][G]);
// 	ft_printf("BLUE:  %s\n", scene.colors[CEILING][B]);
// 	scene.ceiling = get_color(&scene, CEILING);
// 	ft_printf("Hexa value: %X\n", scene.ceiling);

// 	ft_printf("\nMap section:\n");
// 	while (scene.map_list)
// 	{
// 		ft_printf("%s$\n", (char *)scene.map_list->content);
// 		scene.map_list = scene.map_list->next;
// 	}
// 	ft_printf("map width -> %d\n", get_map_width(scene.map_list));
// 	ft_printf("map height-> %d\n", ft_lstsize(scene.map_list));
// 	ft_printf("Starting orientation-> %c\n", scene.spawn_orientation);
// }

/*
void printIntDoublePointerArray(int **array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%2d ", array[i][j]);
        }
        printf("\n");
    }
}
*/

void	print_2d_array(int **array, int height, int width)
{
	int	i;
	int	j;
	// int	value;
	
	i = 0;
	printf("height: %d\n", height);
	printf("width: %d\n", width);
	while (i < height)
	{
		printf("row %2d-> ", i);
		j = 0;
		while (j < width)
		{
			if (array[i][j] == -2)
				break;
			printf("[%2d] ", array[i][j]);
			// value = array[i][j];
			// if (value == 1)
			// 	printf("%s█%s", VIOLET, RESET);
			// if (value == 0)
			// 	printf("%s█%s", MAGENTA, RESET);
			// if (value == -1)
			// 	printf("%s█%s", ORANGE, RESET);
			// if (value == -2)
			// 	printf("%s█%s", RED, RESET);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

int	main(int argc, char **argv)
{
	t_scene	scene;
	// t_cub	cub;

	validate_arguments(argc, argv);

	scene = parse_cubfile(argv[1]);

	// test_parsing(scene); //tmp
/* ************************************************************************** */
	
	int		width = get_map_width(scene.map_list);
	int		height = ft_lstsize(scene.map_list);
	ft_printf("map width: %d\nmap height: %d\n", width, height);

	ft_printf("\nTesting map_array\n");
	int		**map_array = get_2d_map(scene.map_list, height, width);
	
	if (!map_array)
		ft_printf("No 2d array\n");
	else
		print_2d_array(map_array, width, height);
		// ft_printf("We have the 2d array\n");


	// cub = init_cub(argv[1]);
	// cub.minimap = init_map(&scene);
	// cub.player = init_player((t_point){100,100}, 'S');

	// setup_images(&cub);
	
	

	// cub_loop(&cub);
	// cleanup(&cub);

	return (SUCCESS);
}
