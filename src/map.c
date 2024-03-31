/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:13:03 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/18 13:38:12 by oroy             ###   ########.fr       */
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
	extract_wall_textures(scene, &map, call_cub()->mlx);
	// 
	return (map);
}
