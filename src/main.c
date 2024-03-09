/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/09 11:00:04 by cdumais          ###   ########.fr       */
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

int	**call_array(void)
{
	return (call_cub()->map.map_array);
}

int	call_width(void)
{
	return (call_cub()->map.width);
}

int	call_height(void)
{
	return (call_cub()->map.height);
}

/* ************************************************************************** */

t_cub	*init_cub(char *filepath)
{
	t_cub	*cub;
	char	*title;

	cub = call_cub();
	// 
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", FALSE);
	if (!cub->mlx)
		error_mlx();
	// 
	title = ft_strjoin("cub3D - ", filepath);
	mlx_set_window_title(cub->mlx, title);
	free(title);
	// 
	cub->img = new_img(cub->mlx, WIDTH, HEIGHT, true);
	return (cub);	
}

/* **this can be removed once we handle the F, C and I textures

*/
void	setup_images(t_cub *cub)
{
	cub->texture[NO] = load_png("img/bluestone.png", cub->mlx);
	cub->texture[SO] = load_png("img/eagle.png", cub->mlx);
	cub->texture[EA] = load_png("img/redbrick.png", cub->mlx);
	cub->texture[WE] = load_png("img/wood.png", cub->mlx);
	// 
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

/*
*/
int	main(int argc, char **argv)
{
	t_scene	scene;
	t_cub	*cub;

	validate_arguments(argc, argv);
	
	scene = parse_cubfile(argv[1]);
	validate_scene(&scene);
	
	cub = init_cub(argv[1]);
	cub->map = init_map(&scene);
	cub->player = init_player(&scene);
	cleanup_scene(&scene);
	// 
	cub->minimap = init_minimap(cub); //test
	// 
	setup_images(cub);
	cub_loop(cub);
	
	cleanup(cub);
	return (SUCCESS);
}

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
