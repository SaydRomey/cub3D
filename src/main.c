/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/08 13:48:04 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub	*init_cub(char *title)
{
	t_cub	*cub;

	cub = call_cub();
	
	cub->mlx = mlx_init(WIDTH, HEIGHT, title, FALSE);
	if (!cub->mlx)
		error_mlx();
		
	cub->img = new_img(cub->mlx, WIDTH, HEIGHT, true);

	cub->floor_ceiling_default[FLOOR] = "img/checker.png";
	cub->floor_ceiling_default[CEILING] = "img/light.png";

	return (cub);
}

void	parse_and_extract(t_cub *cub, int argc, char **argv)
{
	t_scene	scene;
	t_map	map;
	int		i;

	i = 1;
	while (i < argc)
	{
		if (there_is_a_problem())
			error();
		
		reset_info(); //resets the checklist
		
		scene = parse_cubfile(argv[i]); //parses the info from a cubfile
		validate_scene(&scene);

		map = init_map(&scene); //converts the scene into usable data
		validate_map(&map);
		
		if (!there_is_a_problem())
			add_new_level(&cub->levels, map, argv[i]); //copies the t_map, inits the t_minimap, and creates a t_lvl node
				
		cleanup_scene(&scene);
		cleanup_map(&map);
		i++;
	}
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
	t_cub	*cub;
		
	validate_arguments(argc, argv);
	cub = init_cub(GAME_TITLE);
	
	parse_and_extract(cub, argc, argv);
	
	if (cub->levels)
	{
		// t_map	*map_ptr = get_map(cub->current_level);
		// if (map_ptr)
		// 	test_map(*map_ptr); //tmp, displays info about a specific map
		
		
		cub->player = init_player(get_map(cub->current_level));
		// cub->...
		
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

// 	validate_map(&cub->map);

// 	cub->minimap = init_minimap(cub); //wip

// 	setup_images(cub);
// 	cub_loop(cub);
// 	cleanup(cub);
// 	return (SUCCESS);
// }
