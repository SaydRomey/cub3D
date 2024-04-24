/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:23:57 by olivierroy        #+#    #+#             */
/*   Updated: 2024/04/23 22:56:49 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_hit(int map_x, int map_y)
{
	t_map	*map;

	map = get_map(call_cub()->current_level);
	if (map_x < 0 || map_x >= map->width || 
		map_y < 0 || map_y >= map->height)
		return (1);
	return (map->map_array[map_y][map_x]);
}

t_line	get_stripe_data(float divider, int center, int limit)
{
	t_line	line;

	line.size = ft_abs((int)(HEIGHT / divider));
	line.start = center - (line.size / 2);
	if (line.start < 0)
		line.start = 0;
	line.end = center + (line.size / 2);
	if (line.end >= limit)
		line.end = limit - 1;
	return (line);
}

float	rot_matrix(t_fpoint a, t_fpoint b)
{
	return (a.x * b.y - b.x * a.y);
}

/**
 * Get pixel coordinates according to position in grid.
 * Getting the absolute value (ft_abs) is necessary
 * since there are no negative values in texture.
*/
t_point	get_pixel_in_texture(t_texture tex, t_fpoint pos)
{
	t_point	tex_pos;
	
	tex_pos.x = ft_abs((int)(tex.width * (pos.x - (int) pos.x)));
	tex_pos.y = ft_abs((int)(tex.height * (pos.y - (int) pos.y)));
	return (tex_pos);
}

bool	position_is_elevator(int pos_x, int pos_y)
{
	t_cub	*cub;

	cub = call_cub();
	if ((int)pos_x == cub->elevator.position.x &&
		(int)pos_y == cub->elevator.position.y)
		return (true);
	return (false);
}
