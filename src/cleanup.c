/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:02:54 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/01 22:27:43 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
*/
void	free_map_array(int **map_array, int height)
{
	int	i;

	if (!map_array)
		return ;
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

/*
*/
void	cleanup(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (cub->levels)
	{
		ft_lstclear(&cub->levels, delete_level);
	}
	cleanup_elevator(&cub->elevator);
	mlx_delete_image(cub->mlx, cub->img);
	mlx_delete_image(cub->mlx, cub->radar_img);
	mlx_delete_image(cub->mlx, cub->user_img);
	// mlx_delete_image(cub->mlx, cub->menu_img);
	mlx_terminate(cub->mlx);
	free(cub);
}

/*
frees allocated memory in a t_scene struct
(strings and a linked list of strings)
*/
void	cleanup_scene(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < WALL_TEXTURE_LEN)
	{
		if (scene->wall_textures[i])
			free(scene->wall_textures[i]);
	}
	i = -1;
	while (++i < COLOR_TYPE_LEN)
	{
		if (scene->floor_ceiling_textures[i])
			free(scene->floor_ceiling_textures[i]);
	}
	i = -1;
	while (++i < RGB_LEN)
	{
		if (scene->colors[FLOOR][i])
			free(scene->colors[FLOOR][i]);
		if (scene->colors[CEILING][i])
			free(scene->colors[CEILING][i]);
	}
	if (scene->map_list)
		ft_lstclear(&scene->map_list, free);
}

/*
frees allocated memory in a t_map struct
*/
void	cleanup_map(t_map *map)
{
	int	i;

	free_map_array(map->map_array, map->height);
	i = 0;
	while (i < WALL_TEXTURE_LEN)
	{
		if (map->wall_textures_img[i])
			mlx_delete_image(call_cub()->mlx, map->wall_textures_img[i]);
		i++;
	}
	i = 0;
	while (i < COLOR_TYPE_LEN)
	{
		if (map->floor_ceiling_img[i])
			mlx_delete_image(call_cub()->mlx, map->floor_ceiling_img[i]);
		i++;
	}
}

void	cleanup_elevator(t_elevator *elevator)
{
	mlx_t	*mlx;
	int		i;

	mlx = call_cub()->mlx;
	i = 0;
	while (i < ELEVATOR_TEX_LEN)
	{
		if (elevator->texture[i])
			mlx_delete_image(mlx, elevator->texture[i]);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (elevator->buttons[0].button_imgs[i])
			mlx_delete_image(mlx, elevator->buttons[0].button_imgs[i]);
		if (elevator->buttons[1].button_imgs[i])
			mlx_delete_image(mlx, elevator->buttons[1].button_imgs[i]);
		i++;
	}
	free_animation(&elevator->door_animation);
}
