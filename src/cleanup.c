/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:02:54 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/06 17:50:21 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_scene(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < WALL_TEXTURE_LEN)
	{
		if (scene->wall_textures[i])
			free(scene->wall_textures[i]);
		i++;
	}
	i = 0;
	while (i < RGB_LEN)
	{
		if (scene->colors[FLOOR][i])
			free(scene->colors[FLOOR][i]);
		if (scene->colors[CEILING][i])
			free(scene->colors[CEILING][i]);
		i++;
	}
	if (scene->map_list)
		ft_lstclear(&scene->map_list, free); //tmp, this should be handled in the map part..?
	proof("t_scene cleaned up");
}

void	cleanup_map(t_map *map)
{
	free_map(map->map_array, map->height);
	proof("t_map cleaned up");
}

/*
free everything from here
*/
void	cleanup(t_cub *cub)
{
	// our allocations:
	cleanup_map(&cub->map);
	
	// mlx allocations:
	mlx_delete_image(cub->mlx, cub->img);
	mlx_terminate(cub->mlx);
	proof("mlx terminated");
}

void	call_clean(void)
{
	ft_printf("*!*!*! call cleaned\n");
	cleanup(call_cub());
}
