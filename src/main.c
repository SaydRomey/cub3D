/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/25 15:35:04 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub	*call_cub(void)
{
	static t_cub	*cub;

	if (cub == NULL)
	{
		cub = ft_calloc(1, sizeof(*cub));
		if (!cub)
			return (NULL);
	}
	return (cub);
}

/*	**should this function be static or not ?

*/
static t_cub	*init_cub(char *title)
{
	t_cub	*cub;

	cub = call_cub();
	cub->mlx = mlx_init(WIDTH, HEIGHT, title, false);
	if (!cub->mlx)
		error_mlx();
	cub->img = new_img(cub->mlx, WIDTH, HEIGHT, true);
	cub->radar_img = new_img(cub->mlx, RADAR_SIZE, RADAR_SIZE, true);
	move_img(cub->radar_img, WIDTH - RADAR_SIZE - RADAR_MARGIN, RADAR_MARGIN);
	cub->floor_ceiling_default[FLOOR] = "img/checker.png";
	cub->floor_ceiling_default[CEILING] = "img/light.png";
	return (cub);
}

static void	parse_and_extract(t_cub *cub, int argc, char **argv)
{
	t_scene	scene;
	t_map	map;
	int		i;

	i = 1;
	while (i < argc)
	{
		reset_info();
		scene = parse_cubfile(argv[i]);
		validate_scene(&scene);
		map = init_map(&scene);
		validate_map(&map);
		if (!there_is_a_problem())
			add_new_level(&cub->levels, map, argv[i]);
		cleanup_scene(&scene);
		cleanup_map(&map);
		if (there_is_a_problem())
			error();
		i++;
	}
	// add_segworld(&cub->levels);
}

/*
void	add_segworld(t_list **levels)
{
	t_level	*seg_lvl;
	t_list	*node;

	seg_lvl = (t_level *)ft_calloc(1, sizeof(t_level));
	if (seg_lvl)
	{
		// seg_lvl->...
	}
	else
		set_error("Malloc error");
	if (!there_is_a_problem())
	{
		node = ft_lstnew(seg_lvl);
		if (!node)
		{
			delete_level(seg_lvl);
			set_error("Malloc error");
		}
		else
			ft_lstadd_back(levels, node);
	}
	else
		error();
}
*/

/*
*/
void	update(void *ptr)
{
	t_cub	*cub;
	t_level	*lvl;

	cub = (t_cub *)ptr;
	update_controls(cub);
	update_player(&cub->player);
	update_assets(cub);
	elevator_events(cub);
	lvl = get_level(cub->current_level);
	if (lvl)
	{
		draw_minimap(&lvl->mini, &lvl->map);
		draw_radar(&lvl->mini);
	}
	raycast();
}

/*
	*(tmp)
	ft_printf("Bonus flag: %d\n", BONUS);
	ft_printf("Map chars:  %s\n", MAP_CHARS);

*/
int	main(int argc, char **argv)
{
	t_cub	*cub;
	t_level	*lvl;

	validate_arguments(argc, argv);
	cub = init_cub(GAME_TITLE);
	parse_and_extract(cub, argc, argv);
	if (cub->levels && !there_is_a_problem())
	{
		lvl = get_level(cub->current_level);
		cub->elevator = init_elevator(lvl);
		cub->player = init_player(&lvl->map);
		change_window_title(lvl->filepath);
		draw_minimap(&lvl->mini, &lvl->map);
		draw_floor_ceiling(cub->img, &lvl->map);
		set_mouse(cub);
		mlx_key_hook(cub->mlx, &keyhooks, cub);
		mlx_loop_hook(cub->mlx, update, cub);
		mlx_loop(cub->mlx);
	}
	cleanup(cub);
	free_info();
	return (SUCCESS);
}
