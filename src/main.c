/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/31 12:19:58 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

// t_vfx	setup_vfx(void)
// {
// 	t_vfx	vfx;
	
// 	ft_memset(&vfx, 0, sizeof(t_vfx));

// 	vfx.fog_color = (int)HEX_GREEN;
// 	vfx.floor_fog_color = (int)HEX_PURPLE;
// 	vfx.floor_fog_level = 0.9f;
	
// 	return (vfx);
// }

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

static int	get_scene_total(int argc)
{
	if (argc - 1 < SCENE_LIMIT)
		return (argc - 1);
	else
		return (SCENE_LIMIT);
}

/*
*/
int	main(int argc, char **argv)
{
	t_scene	scene;
	t_map	*maps;
	t_cub	*cub = NULL;
	int		total;
	int		i;

	// call_info()->print_proof = true; //test

	// validate_arguments(argc, argv);
	
	i = 1;
	total = get_scene_total(argc);
	maps = ft_calloc(total, sizeof (t_map));
	if (!maps)
		printf ("Free and Exit\n");
	while (i <= total)
	{
		// 
		call_info()->found_direction = false;
		ft_memset(call_info()->wall_check, 0, sizeof (bool) * WALL_TEXTURE_LEN);
		ft_memset(call_info()->color_check, 0, sizeof (bool) * COLOR_TYPE_LEN);
		//
		scene = parse_cubfile(argv[i]);
		validate_scene(&scene);
		//
		if (i == 1)
		{
			cub = init_cub(argv[1]);
			cub->player = init_player(&scene);
		}
		maps[i - 1] = init_map(&scene);
		cleanup_scene(&scene);
		//
		validate_map(&maps[i - 1]);
		i++;
	}
	cub->maps = maps;
	cub->scene_total = total;
	cub->map = &cub->maps[0];
	cub->elevator = init_elevator(cub);
	// cub->assets = init_assets();
	//
	cub->mini = init_minimap(cub); //test
	// 
	// cub->vfx = setup_vfx(); //tmp
	// 
	setup_images(cub); //tmp
	// 
	cub_loop(cub);
	cleanup(cub);
	// free_split(cub->paths);
	return (SUCCESS);
}
