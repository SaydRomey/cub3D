/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:23:57 by olivierroy        #+#    #+#             */
/*   Updated: 2024/04/29 19:03:07 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_hit(int map_x, int map_y)
{
	t_map	*map;

	map = get_map(call_cub()->current_level);
	if (map_x < 0 || map_x >= map->width
		|| map_y < 0 || map_y >= map->height)
		return (1);
	return (map->map_array[map_y][map_x]);
}

/**
 * @param divider Used to get the size of the line
 * @param center Used to get the start and end of line
 * @param limit Max posible value on screen 
*/
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

int	get_next_unit(t_raycast *r)
{
	if (r->length.x < r->length.y)
	{
		r->ray.side = 0;
		if (check_hit(r->ray_pos.x + r->step.x, r->ray_pos.y) == 0)
			return (0);
	}
	else
	{
		r->ray.side = 1;
		if (check_hit(r->ray_pos.x, r->ray_pos.y + r->step.y) == 0)
			return (0);
	}
	return (1);
}

t_texture	get_texture_info(mlx_image_t *texture)
{
	t_texture	tex;

	ft_memset(&tex, 0, sizeof (t_texture));
	if (texture)
	{
		tex.to_draw = texture;
		tex.width = (int)tex.to_draw->width;
		tex.height = (int)tex.to_draw->height;
	}
	return (tex);
}
