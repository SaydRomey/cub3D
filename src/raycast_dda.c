/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:49:53 by oroy              #+#    #+#             */
/*   Updated: 2024/04/25 16:11:43 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Hit data useful for drawing walls.
 * Note that this function is called twice when the elevator is open and visible
 * 
 * @param wall_perp_dist Perpendicular distance to camera plane
 * @param wall_hit_pos Position on wall (number between 0 and 1)
*/
static void	get_hit_data(float *wall_perp_dist, float *wall_hit_pos)
{
	t_player	*p;
	t_raycast	*r;

	p = &call_cub()->player;
	r = &call_cub()->raycast;
	if (r->ray.side == 0)
	{
		if (r->length.x < r->grid_dist.x)
			*wall_perp_dist = r->length.x;
		else
			*wall_perp_dist = r->length.x - r->grid_dist.x;
		*wall_hit_pos = p->position.y + *wall_perp_dist * r->ray_dir.y;
	}
	else
	{
		if (r->length.y < r->grid_dist.y)
			*wall_perp_dist = r->length.y;
		else
			*wall_perp_dist = r->length.y - r->grid_dist.y;
		*wall_hit_pos = p->position.x + *wall_perp_dist * r->ray_dir.x;
	}
	*wall_hit_pos -= floor(*wall_hit_pos);
}

static void	get_door_hit_data(t_raycast *r)
{
	r->ray_hits_opened_door = true;
	r->ray_pos_door = r->ray_pos;
	r->ray_door.side = r->ray.side;
	get_hit_data(&r->ray_door.wall_perp_dist, &r->ray_door.wall_hit_pos);
}

static bool	check_if_is_inside_elevator(t_cub *cub, t_raycast *r)
{
	if (check_hit(r->ray_pos.x, r->ray_pos.y) == ELEVATOR
		&& get_next_unit(r) == 0)
	{
		if (cub->elevator.door_animation.current_frame != 0)
			get_door_hit_data(r);
		else
			return (1);
	}
	return (0);
}

static void	increment_ray(t_raycast *r)
{
	if (r->length.x < r->length.y)
	{
		r->length.x += r->grid_dist.x;
		r->ray_pos.x += r->step.x;
		r->ray.side = 0;
	}
	else
	{
		r->length.y += r->grid_dist.y;
		r->ray_pos.y += r->step.y;
		r->ray.side = 1;
	}
}

/**
 * DDA (Digital Differential Analyzer):
 * The ray increments of 1 unit in a specific direction
 * until it hits a line on the grid.
 * side 0 = East and West
 * side 1 = North and South
*/
void	execute_dda_algo(t_cub *cub, t_raycast *r)
{
	bool	hit;

	hit = check_if_is_inside_elevator(cub, r);
	while (!hit)
	{
		increment_ray(r);
		if (check_hit(r->ray_pos.x, r->ray_pos.y) > 0)
		{
			if (check_hit(r->ray_pos.x, r->ray_pos.y) == ELEVATOR
				&& cub->elevator.door_animation.current_frame != 0)
				get_door_hit_data(r);
			else
				hit = 1;
		}
	}
	get_hit_data(&r->ray.wall_perp_dist, &r->ray.wall_hit_pos);
}
