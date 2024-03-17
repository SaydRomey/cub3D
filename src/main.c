/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/16 22:53:08 by cdumais          ###   ########.fr       */
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
	cub->texture[F] = load_png("img/wood.png", cub->mlx);
	cub->texture[C] = load_png("img/wood.png", cub->mlx);
	// cub->texture[C] = load_png("img/pikachu.png", cub->mlx);
	cub->texture[I] = load_png("img/pokeball.png", cub->mlx);
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

/*
*/
int	main(int argc, char **argv)
{
	t_scene	scene;
	t_cub	*cub;

	// call_info()->print_proof = true; //test

	validate_arguments(argc, argv);
	
	scene = parse_cubfile(argv[1]);
	validate_scene(&scene);
	
	cub = init_cub(argv[1]);
	cub->map = init_map(&scene);
	cub->player = init_player(&scene);
	cleanup_scene(&scene);
	// 
	validate_map(&cub->map);
	// 
	cub->mini = init_minimap(cub); //test
	// 
	// cub->vfx = setup_vfx(); //tmp
	// 
	setup_images(cub); //tmp
	// 
	cub_loop(cub);
	cleanup(cub);
	return (SUCCESS);
}
