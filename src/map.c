/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:13:03 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/04 18:53:02 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	map.spawn_orientation = scene->spawn_orientation;
	map.starting_position = scene->starting_position;

	proof("map init");

	return (map);
}
