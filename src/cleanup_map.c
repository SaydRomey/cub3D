/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:45:38 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/18 14:42:45 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* **check if 'free_matrix()' from libft does the trick instead..

*/ 
void	free_map_array(int **map_array, int height)
{
	int	i;

	if (!map_array)
		return;
	i = 0;
	while (i < height)
	{
		if (map_array[i])
			free(map_array[i]);
		i++;
	}
	free(map_array);
}

/* ************************************************************************** */
/* ************************************************************************** */

static void	cleanup_wall_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < WALL_TEXTURE_LEN)
	{
		if (map->wall_textures_img[i])
			mlx_delete_image(call_cub()->mlx, map->wall_textures_img[i]);
		i++;
	}
}

static void	cleanup_floor_ceiling_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < COLOR_TYPE_LEN)
	{
		if (map->floor_ceiling_img[i])
			mlx_delete_image(call_cub()->mlx, map->floor_ceiling_img[i]);
		i++;
	}
}

/*
frees allocated memory in a t_map struct
*/
void	cleanup_map(t_map *map)
{
	free_map_array(map->map_array, map->height);
	// free_matrix(map->map_array); //to test
	cleanup_wall_textures(map);
	cleanup_floor_ceiling_textures(map);
}
