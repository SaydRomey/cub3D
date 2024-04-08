/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:23:57 by olivierroy        #+#    #+#             */
/*   Updated: 2024/04/08 11:49:59 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_hit(int map_x, int map_y)
{
	t_map	*map;

	// map = call_cub()->map;
	map = get_map(call_cub()->current_level);
	
	if (map_x < 0 || map_x >= map->width || 
		map_y < 0 || map_y >= map->height)
		return (1);
	return (map->map_array[map_y][map_x]);
}

t_point	update_texture_position(t_texture tex, t_fpoint pos)
{
	t_point	tex_pos;
	
	tex_pos.x = ft_abs((int)(tex.width * (pos.x - (int) pos.x)));
	tex_pos.y = ft_abs((int)(tex.height * (pos.y - (int) pos.y)));
	return (tex_pos);
}
