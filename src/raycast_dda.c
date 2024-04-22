/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:49:53 by oroy              #+#    #+#             */
/*   Updated: 2024/04/10 20:02:30 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	get_elevator_hit_data(t_cub *cub, t_raycast *r)
{
	cub->elevator.door_open = true;
	r->ray_pos_door = r->ray_pos;
	r->ray_door.side = r->ray.side;
	get_hit_data(&r->ray_door.wall_perp_dist, &r->ray_door.wall_hit_pos);
}

static int	get_next_unit(t_raycast *r)
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

static bool	check_inside_elevator(t_cub *cub, t_raycast *r)
{
	if (check_hit(r->ray_pos.x, r->ray_pos.y) == ELEVATOR
		&& get_next_unit(r) == 0)
	{
		if (cub->elevator.door_animation.current_frame != 0)
			get_elevator_hit_data(cub, r);
		else
			return (1);
	}
	return (0);
}

void	execute_dda_algo(t_cub *cub, t_raycast *r)
{
	bool	hit = 0;

	hit = check_inside_elevator(cub, r);
	while (!hit)
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
		if (check_hit(r->ray_pos.x, r->ray_pos.y) > 0)
		{
			if (check_hit(r->ray_pos.x, r->ray_pos.y) == ELEVATOR
				&& cub->elevator.door_animation.current_frame != 0)
				get_elevator_hit_data(cub, r);
			else
				hit = 1;
		}
	}
	get_hit_data(&r->ray.wall_perp_dist, &r->ray.wall_hit_pos);
}
