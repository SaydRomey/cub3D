/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:02:54 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/10 15:36:33 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_texture_paths(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < WALL_TEXTURE_LEN)
	{
		if (scene->wall_textures[i])
			free(scene->wall_textures[i]);
		i++;
	}
	proof("scene wall texture paths freed");
	i = 0;
	while (i < COLOR_TYPE_LEN)
	{
		if (scene->floor_ceiling_textures[i])
			free(scene->floor_ceiling_textures[i]);
		i++;
	}
	proof("scene floor/ceiling texture paths freed");
}

static void	free_rgb_strings(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < RGB_LEN)
	{
		if (scene->colors[FLOOR][i])
			free(scene->colors[FLOOR][i]);
		if (scene->colors[CEILING][i])
			free(scene->colors[CEILING][i]);
		i++;
	}
	proof("scene rgb strings freed");
}

/*
frees allocated memory in a t_scene struct
(strings and a linked list of strings)
*/
void	cleanup_scene(t_scene *scene)
{
	free_texture_paths(scene);
	free_rgb_strings(scene);
	if (scene->map_list)
		ft_lstclear(&scene->map_list, free);
	proof("t_scene cleaned up");
}

/* ************************************************************************** */
/* ************************************************************************** */

/* **maybe make this a more generic function (in libft)?

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
		{
			mlx_delete_image(call_cub()->mlx, map->wall_textures_img[i]);
			vaproof("Deleted wall texture image %d", i);
		}
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
		{
			mlx_delete_image(call_cub()->mlx, map->floor_ceiling_img[i]);
			if (i == FLOOR)
				vaproof("Deleted floor texture image %d", i);
			else if (i == CEILING)
				vaproof("Deleted ceiling texture image %d", i);
		}
		i++;
	}
}

/*
frees allocated memory in a t_map struct
*/
void	cleanup_map(t_map *map)
{
	free_map_array(map->map_array, map->height);
	cleanup_wall_textures(map);
	cleanup_floor_ceiling_textures(map);
	proof("t_map cleaned up");
}

/* ************************************************************************** */

/*
frees t_cub and mlx ressources
*/
void	cleanup(t_cub *cub)
{
	
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
