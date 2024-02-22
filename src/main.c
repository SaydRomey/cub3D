/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/22 13:57:29 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub	init_cub(char *map_path)
{
	t_cub	cub;
	char	*title;

	title = ft_strjoin("cub3D - ", map_path);
	ft_memset(&cub, 0, sizeof(t_cub));
	cub.mlx = mlx_init(WIDTH, HEIGHT, title, FALSE);
	free(title);
	if (!cub.mlx)
		error();
	cub.img = mlx_new_image(cub.mlx, WIDTH, HEIGHT);
	if (!cub.img)
		error();
	cub.minimap_img = mlx_new_image(cub.mlx, 512, 512); //to change later?
	if (!cub.minimap_img)
		error();
	return (cub);
}

void	setup_images(t_cub *cub)
{
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) < SUCCESS)
		error();
	if (mlx_image_to_window(cub->mlx, cub->minimap_img, WIDTH - (512), 0) < SUCCESS)
		error();
	// 
	// background(cub->img, 0x404040FF); // draw floor and ceiling here instead
	draw_ceiling(cub->img, cub->minimap.ceiling_color);
	draw_floor(cub->img, cub->minimap.floor_color);
	// 
	draw_background(cub->minimap_img, 0x202020FF);
	draw_minimap(cub->minimap_img, &cub->minimap); //? test without if in update()
}

/*
hooks and loops
*/
void	cub_loop(t_cub *cub)
{
	mlx_key_hook(cub->mlx, &keyhooks, cub);
	mlx_loop_hook(cub->mlx, update, cub);
	
	mlx_loop(cub->mlx);
}


int	main(void)
{
	t_cub	cub;
	
	cub = init_cub("[map title]");
	cub.minimap = init_map();
	cub.player = init_player((t_point){100,100}, 'S');

	setup_images(&cub);

	cub_loop(&cub);
	cleanup(&cub); //?

	return (SUCCESS);
}
