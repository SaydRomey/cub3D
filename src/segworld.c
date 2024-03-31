/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segworld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:07:44 by oroy              #+#    #+#             */
/*   Updated: 2024/03/29 12:41:23 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	call_segworld(t_cub *cub, t_elevator *e, t_fpoint pos, int ori)
// {
// 	int	map[8][8] = 
// 	{
// 		{1, 1, 1, 1, 1, 1, 1, 1},
// 		{1, 0, 1, 3, 1, 0, 0, 1},
// 		{1, 0, 0, 0, 1, 1, 0, 1},
// 		{1, 0, 1, 0, 0, 0, 0, 1},
// 		{1, 0, 1, 1, 1, 1, 0, 1},
// 		{1, 0, 0, 1, 0, 0, 0, 1},
// 		{1, 1, 0, 0, 0, 1, 0, 1},
// 		{1, 1, 1, 1, 1, 1, 1, 1}
// 	};
// 	int	x;
// 	int	y;
	
// 	y = 0;
// 	cub->map.width = 8;
// 	cub->map.height = 8;
// 	cub->map.floor_color = 0x00;
// 	cub->map.ceiling_color = 0x00;
// 	cub->map.wall_textures_img[NO] = load_png("img/checker.png", cub->mlx);
// 	cub->map.wall_textures_img[SO] = load_png("img/paint.png", cub->mlx);
// 	cub->map.wall_textures_img[EA] = load_png("img/pokeball.png", cub->mlx);
// 	cub->map.wall_textures_img[WE] = load_png("img/tree_trunk.png", cub->mlx);
// 	free_matrix(cub->map.map_array);
// 	cub->map.map_array = ft_calloc(cub->map.height, sizeof (int *));
// 	if (!cub->map.map_array)
// 		printf ("Malloc error\n");
// 	while (y < cub->map.height)
// 	{
// 		x = 0;
// 		cub->map.map_array[y] = ft_calloc(cub->map.width, sizeof (int));
// 		if (!cub->map.map_array[y])
// 			printf ("Malloc error\n");
// 		while (x < cub->map.width)
// 		{
// 			cub->map.map_array[y][x] = map[y][x];
// 			x++;
// 		}
// 		y++;
// 	}
// 	parse_elevator(&cub->map, e);
// 	e->id = -1;
// 	update_elevator_struct(cub, *e);
// 	change_character_coordinates(cub, pos, ori);
// }
