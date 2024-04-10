/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/10 15:10:10 by cdumais          ###   ########.fr       */
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

	// cub->elevator_textures/buttons ... ?

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
			add_new_level(&cub->levels, map, argv[i]); //copies the t_map and images, inits the t_minimap, and creates a t_lvl node
				
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
		
		t_level	*lvl = get_level(cub->current_level);
		
		change_window_title(lvl->filepath);
		draw_minimap(&lvl->mini, &lvl->map);
		cub->player = init_player(get_map(cub->current_level));
		
		cub_loop(cub);
	}
	cleanup(cub);
	free_info();
	return (SUCCESS);	
}
