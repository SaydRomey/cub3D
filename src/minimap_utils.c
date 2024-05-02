/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:47:11 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/02 00:21:30 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
this has a generic version in pixel_colors.c

*/
static int	compute_wall_average(int *averages, int count)
{
	int	total[4];
	int	result_color;
	int	i;

	total[R] = 0;
	total[G] = 0;
	total[B] = 0;
	total[A] = 0;
	i = 0;
	while (i < count)
	{
		total[R] += get_red(averages[i]);
		total[G] += get_green(averages[i]);
		total[B] += get_blue(averages[i]);
		total[A] += get_alpha(averages[i]);
		i++;
	}
	total[R] /= count;
	total[G] /= count;
	total[B] /= count;
	total[A] /= count;
	result_color = combine_rgba(total[R], total[G], total[B], total[A]);
	return (result_color);
}

static int	average_wall_color(t_map *map)
{
	int	averages[4];

	averages[NO] = average_img_color(map->wall_textures_img[NO]);
	averages[SO] = average_img_color(map->wall_textures_img[SO]);
	averages[EA] = average_img_color(map->wall_textures_img[EA]);
	averages[WE] = average_img_color(map->wall_textures_img[WE]);
	return (compute_wall_average(averages, WALL_TEXTURE_LEN));
}

void	set_minimap_colors(t_map *map, int *colors)
{
	if (map->floor_ceiling_img[FLOOR])
		colors[WALKABLE] = average_img_color(map->floor_ceiling_img[FLOOR]);
	else
		colors[WALKABLE] = MINI_WALK_COL;
	colors[WALL] = average_wall_color(map);
	colors[DOOR] = MINI_DOOR_COL;
	colors[ELEVATOR] = MINI_ELEV_COL;
}
