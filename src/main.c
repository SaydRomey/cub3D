/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/11 19:32:25 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_default_texture_paths(t_cub *cub)
{
	cub->floor_ceiling_default[FLOOR] = "img/checker.png";
	cub->floor_ceiling_default[CEILING] = "img/light.png";

	// cub->elevator...
	
	// elevator / UI paths here.. ?
}

t_cub	*init_cub(char *title)
{
	t_cub	*cub;

	cub = call_cub();
	
	cub->mlx = mlx_init(WIDTH, HEIGHT, title, FALSE);
	if (!cub->mlx)
		error_mlx();
		
	cub->img = new_img(cub->mlx, WIDTH, HEIGHT, true);
	// cub->user_interface = new_img(cub->mlx, WIDTH, HEIGHT, true);

	setup_default_texture_paths(cub);

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

int	main(int argc, char **argv)
{
	t_cub	*cub;
	t_level	*lvl = NULL;
		
	validate_arguments(argc, argv);
	cub = init_cub(GAME_TITLE);
	parse_and_extract(cub, argc, argv);
	if (cub->levels && !there_is_a_problem())
	{
		lvl = get_level(cub->current_level);
		
		if (lvl->elevator_exists)
			cub->elevator = init_elevator(cub);
	
		cub->player = init_player(&lvl->map);

		change_window_title(lvl->filepath);
		draw_minimap(&lvl->mini, &lvl->map);

		set_mouse(cub);
		mlx_key_hook(cub->mlx, &keyhooks, cub);
		mlx_loop_hook(cub->mlx, update, cub);
		mlx_loop(cub->mlx);
	}
	cleanup(cub);
	free_info();
	return (SUCCESS);	
}
