/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:44:45 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/22 17:59:02 by cdumais          ###   ########.fr       */
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
	i = 0;
	while (i < COLOR_TYPE_LEN)
	{
		if (scene->floor_ceiling_textures[i])
			free(scene->floor_ceiling_textures[i]);
		i++;
	}
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
}
