/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:02:54 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/03 15:49:56 by cdumais          ###   ########.fr       */
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
		ft_lstclear(&scene->map_list, free);
	proof("t_scene cleaned up");
}

void	cleanup_map(t_map *map)
{
	free_map(map->map_array, map->height);
	cleanup_wall_textures(map);
	proof("t_map cleaned up");
}

/*
free everything from here
*/
void	cleanup(t_cub *cub)
{
	// int	idx;
	
	// idx = 0;
	// while (idx < cub->scene_total)
	// {
	// 	cleanup_map(&cub->maps[idx]);
	// 	idx++;
	// }
	// cleanup_minimap(&cub->mini);
	
	// int	i = 0;
	// while (i < 6)
	// {
	// 	if (cub->texture[i])
	// 	{
	// 		mlx_delete_image(cub->mlx, cub->texture[i]);
	// 		vaproof("Deleted bonus texture %d", i);
	// 	}
	// 	i++;
	// }
	
	if (cub->levels)
	{
		ft_lstclear(&cub->levels, delete_level);
		proof("lstcleared levels");
	}
	
	// mlx allocations:
	mlx_delete_image(cub->mlx, cub->img);
	mlx_terminate(cub->mlx);
	proof("mlx terminated");
}

/*
test function
*/
void	call_clean(void)
{
	proof("called clean");
	cleanup(call_cub());
}
