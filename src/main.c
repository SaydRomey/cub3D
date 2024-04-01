/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/01 01:24:45 by cdumais          ###   ########.fr       */
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
	mlx_set_window_title(cub->mlx, title); //should we rechange it for other levels ?
	free(title);
	
	cub->img = new_img(cub->mlx, WIDTH, HEIGHT, true);
	return (cub);
}

/* **this can be removed once we handle the F, C and I textures (maybe use a t_bonus struct ?)

*/
void	setup_images(t_cub *cub)
{
	cub->texture[F] = load_png("img/checker.png", cub->mlx);
	cub->texture[C] = load_png("img/light.png", cub->mlx);
	// cub->texture[C] = load_png("img/pikachu.png", cub->mlx);
	cub->texture[I] = load_png("img/pokeball.png", cub->mlx);
	cub->texture[J] = load_png("img/tree_trunk.png", cub->mlx);
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
typedef struct s_level
{
	t_map		map;
	// t_minimap	mini;
	// other relevant info like level index (to navigate to 'lvl->index + 1' for next floor..)
	
}			t_level;

void	add_new_level(t_list **levels, t_map map)
{
	t_level	*new_level;
	t_list	*node;

	new_level = (t_level *)malloc(sizeof(t_level));
	if (!new_level)
		return ; //malloc error
	
	new_level->map = map;
	// add other parameters later..
	
	node = ft_lstnew(new_level);
	if (!node)
	{
		free(new_level);
		return ; //malloc error
	}
	ft_lstadd_back(levels, new_node);
}

void	del_level(void *level)
{
	t_level	*lvl;
	
	lvl = (t_level *)level;
	// specific cleanup here... (scene, map, etc)
	free(lvl);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;
	t_list	*levels = NULL;
	t_scene	scene;
	t_map	*maps;
	int		i;

	// call_info()->print_proof = true;

	validate_arguments(argc, argv);
	cub = init_cub(argv[1]);
	cub->player = init_player()
	i = 1;
	while (i < argc)
	{
		// reset the checklist for new cubfile parsing
		scene = parse_cubfile(argv[i]);
		validate_scene(&scene);
		map = init_map(&scene);
		if (i == 1)
		{
			cub->player = init_player(&scene);
		}
		cleanup_scene(&scene);
		validate_map(&map);
		add_new_level(&levels, map);
		i++;
	}
	if (levels)
	{
		cub->levels = levels;
		
		// cub->current_level = ft_lstget(levels, 0);
		
		cub->elevator = init_elevator(cub);
		
		// other setup ? like setup image or something else if needed
		cub_loop(cub);
	}
	ft_lstclear(&levels, del_level);
	cleanup(cub);
	return (SUCCESS);	
}

// we could then use
t_list	*ft_lstget(t_list *lst, int index);
// to navigate to the desired level..

// also maybe add a check that if we have an elevator but only one level,
// we introduce segworld :D



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

