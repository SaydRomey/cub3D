/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:13:03 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/06 14:48:00 by cdumais          ###   ########.fr       */
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
	// 
	map.floor_color = get_color(scene, FLOOR);
	map.ceiling_color = get_color(scene, CEILING);
	// 
	// map.wall_textures_img = extract_wall_textures(scene);
	// 
	// map.tile_size = 64;
	// map.wall_tile_color = HEX_BLACK;
	// map.floor_tile_color = HEX_WHITE;
	// map.background_color = HEX_GRAY;
	// 
	return (map);
}
