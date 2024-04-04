/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/03 21:32:56 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub	*init_cub(char *filepath)
{
	t_cub	*cub;
	char	*title;

	cub = call_cub();
	
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", FALSE);
	if (!cub->mlx)
		error_mlx();
	
	title = ft_strjoin("cub3D - ", filepath);
	mlx_set_window_title(cub->mlx, title); //should we rechange it for other levels ? (keep the path in t_level)
	free(title);
	
	cub->img = new_img(cub->mlx, WIDTH, HEIGHT, true);
	return (cub);
}

/* **this can be removed once we handle the F, C and I textures (maybe use a t_bonus struct ?)

*/
// void	setup_images(t_cub *cub)
// {
// 	cub->texture[F] = load_png("img/checker.png", cub->mlx);
// 	cub->texture[C] = load_png("img/light.png", cub->mlx);
// 	// cub->texture[C] = load_png("img/pikachu.png", cub->mlx);
// 	cub->texture[I] = load_png("img/pokeball.png", cub->mlx);
// 	cub->texture[J] = load_png("img/tree_trunk.png", cub->mlx);
// }

/*
hooks and loops
*/
void	cub_loop(t_cub *cub)
{
	// set_mouse(cub);
	mlx_key_hook(cub->mlx, &keyhooks, cub);
	mlx_loop_hook(cub->mlx, update, cub);
	mlx_loop(cub->mlx);
}

/*
*/
int	main(int argc, char **argv)
{
	t_cub	*cub;
	t_scene	scene;
	int		i;

	call_info()->print_proof = true; //comment to disable debug messages in terminal
		
	validate_arguments(argc, argv);
	cub = init_cub(argv[1]);
	i = 1;
	while (i < argc)
	{
		// if (there_is_a_problem())
			// error();
		reset_info();
		scene = parse_cubfile(argv[i]);
		validate_scene(&scene);
		add_new_level(&cub->levels, scene, argv[i]);
		cleanup_scene(&scene);
		i++;
	}
	if (cub->levels)
	{
		// t_map	*map_ptr = get_map(cub->levels, 0);
		// test_map(*map_ptr);
		
		cub->player = init_player(get_map(cub->levels, cub->current_level));
		
		cub_loop(cub);
	}
	cleanup(cub);
	free_info();
	return (SUCCESS);	
}


/* ************************************************************************** */
/* ************************************************************************** */

// static int	get_scene_total(int argc)
// {
// 	if (argc - 1 < SCENE_LIMIT)
// 		return (argc - 1);
// 	else
// 		return (SCENE_LIMIT);
// }

// /*
// */
// int	main(int argc, char **argv)
// {
// 	t_scene	scene;
// 	t_map	*maps;
// 	t_cub	*cub = NULL;
// 	int		total;
// 	int		i;


// 	// validate_arguments(argc, argv);
	
// 	i = 1;
// 	total = get_scene_total(argc);
// 	maps = ft_calloc(total, sizeof(t_map));
// 	if (!maps)
// 		printf ("Free and Exit\n");
// 	while (i <= total)
// 	{
// 		// 
// 		call_info()->found_direction = false;
// 		ft_memset(call_info()->wall_check, 0, sizeof (bool) * WALL_TEXTURE_LEN);
// 		ft_memset(call_info()->color_check, 0, sizeof (bool) * COLOR_TYPE_LEN);
// 		//
// 		scene = parse_cubfile(argv[i]);
// 		validate_scene(&scene);
// 		//
// 		if (i == 1)
// 		{
// 			cub = init_cub(argv[1]);
// 			cub->player = init_player(&scene);
// 		}
// 		maps[i - 1] = init_map(&scene);
// 		cleanup_scene(&scene);
// 		//
// 		validate_map(&maps[i - 1]);
// 		i++;
// 	}
// 	cub->maps = maps;
// 	cub->scene_total = total;
// 	cub->map = &cub->maps[0];
// 	cub->elevator = init_elevator(cub);
// 	// cub->assets = init_assets();
// 	//
// 	cub->mini = init_minimap(cub);
// 	// 
// 	setup_images(cub); //tmp
// 	// 
// 	cub_loop(cub);
// 	cleanup(cub);
// 	// free_split(cub->paths);
// 	return (SUCCESS);
// }


/* ************************************************************************** */
/* ************************************************************************** */

// int	main(int argc, char **argv)
// {
// 	t_scene	scene;
// 	t_cub	*cub;

// 	validate_arguments(argc, argv);
	
// 	scene = parse_cubfile(argv[1]);
// 	validate_scene(&scene);
	
// 	cub = init_cub(argv[1]);
// 	cub->map = init_map(&scene);
// 	cub->player = init_player(&scene);
// 	cleanup_scene(&scene);

// 	setup_images(cub);
// 	cub_loop(cub);
	
// 	cleanup(cub);
// 	return (SUCCESS);
// }

// int	main_bonus(int argc, char **argv)
// {
// 	t_scene	scene;
// 	t_cub	*cub;

// 	validate_arguments_bonus(argc, argv); //if any two maps can be entered
	
// 	scene = parse_cubfile(argv[1]);
// 	validate_scene(&scene);
	
// 	cub = init_cub(argv[1]);
// 	cub->map = init_map(&scene);
// 	cub->player = init_player(&scene);
// 	cleanup_scene(&scene);
	
// 	scene = parse_cubfile(argv[2]);
// 	validate_scene(&scene);
// 	cub->next_map = init_map(&scene);
// 	cub->next_player = init_player(&scene);
// 	cleanup_scene(&scene);
	
// 	setup_images(cub);
// 	cub_loop(cub);
	
// 	cleanup(cub);
// 	return (SUCCESS);
// }

