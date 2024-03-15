/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:49:53 by oroy              #+#    #+#             */
/*   Updated: 2024/03/14 13:07:30 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_hit_data(t_player *p, t_raycast *r)
{
	if (r->side == 0)
	{
		r->wall_perp_dist = r->length.x - r->grid_dist.x;
		r->wall_hit_pos = p->position.y + r->wall_perp_dist * r->ray_dir.y;
	}
	else
	{
		r->wall_perp_dist = r->length.y - r->grid_dist.y;
		r->wall_hit_pos = p->position.x + r->wall_perp_dist * r->ray_dir.x;
	}
	r->wall_hit_pos -= floor(r->wall_hit_pos);
}

int	check_hit(int map_x, int map_y)
{
	t_map	map;

	map = call_cub()->map;
	if (map_x < 0 || map_x >= map.width || 
		map_y < 0 || map_y >= map.height)
		return (1);
	return (map.map_array[map_y][map_x]);
}

void	execute_dda_algo(t_player *p, t_raycast *r)
{
	bool	hit;

	hit = 0;
	while (!hit)
	{
		if (r->length.x < r->length.y)
		{
			r->length.x += r->grid_dist.x;
			r->ray_pos.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->length.y += r->grid_dist.y;
			r->ray_pos.y += r->step.y;
			r->side = 1;
		}
		if (check_hit(r->ray_pos.x, r->ray_pos.y) > 0)
			hit = 1;
	}
	get_hit_data(p, r);
}
