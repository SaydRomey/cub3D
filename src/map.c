/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:13:03 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/01 15:00:25 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	color_is_invalid(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (TRUE);
	return (FALSE);
}

int	get_color(t_scene *scene, int id)
{
	int	r;
	int	g;
	int	b;
	int	a;
	int	color_int;

	r = ft_atoi(scene->colors[id][R]);
	g = ft_atoi(scene->colors[id][G]);
	b = ft_atoi(scene->colors[id][B]);
	a = 0xFF;
	if (color_is_invalid(r, g, b))
	{
		return (0x000000FF);
	}
	color_int = combine_rgba(r, g, b, a);
	return (color_int);
}

/* ************************************************************************** */

static void	extract_wall_textures(t_scene *scene, t_map *map, mlx_t *mlx)
{
	int	i;

	i = 0;
	while (i < WALL_TEXTURE_LEN)
	{
		if (scene->wall_textures[i])
			map->wall_textures_img[i] = load_png(scene->wall_textures[i], mlx);
		else
			map->wall_textures_img[i] = NULL;
		i++;
	}
}

static void	extract_floor_ceiling_textures(t_scene *scene, \
t_map *map, mlx_t *mlx)
{
	int		i;

	i = 0;
	while (i < COLOR_TYPE_LEN)
	{
		if (scene->floor_ceiling_textures[i])
			map->floor_ceiling_img[i] = \
		load_png(scene->floor_ceiling_textures[i], mlx);
		else
			map->floor_ceiling_img[i] = \
		load_png(call_cub()->floor_ceiling_default[i], mlx);
		i++;
	}
}

t_map	init_map(t_scene *scene)
{
	t_map	map;

	ft_memset(&map, 0, sizeof(t_map));
	map.height = ft_lstsize(scene->map_list);
	map.width = get_map_width(scene->map_list);
	map.map_array = get_2d_map(scene->map_list, map.height, map.width);
	if (!map.map_array)
		set_error("malloc error in init_map");
	map.floor_color = get_color(scene, FLOOR);
	map.ceiling_color = get_color(scene, CEILING);
	extract_wall_textures(scene, &map, call_cub()->mlx);
	extract_floor_ceiling_textures(scene, &map, call_cub()->mlx);
	map.spawn_orientation = scene->spawn_orientation;
	map.starting_position = scene->starting_position;
	return (map);
}
