/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:23:33 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/02 16:44:58 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_initial_offset(t_player *p, t_raycast *r)
{
	if (r->ray_dir.x < 0)
	{
		r->step.x = -1;
		r->length.x = (p->position.x - r->ray_pos.x) * r->grid_dist.x;
	}
	else
	{
		r->step.x = 1;
		r->length.x = (r->ray_pos.x + 1.0 - p->position.x) * r->grid_dist.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->step.y = -1;
		r->length.y = (p->position.y - r->ray_pos.y) * r->grid_dist.y;
	}
	else
	{
		r->step.y = 1;
		r->length.y = (r->ray_pos.y + 1.0 - p->position.y) * r->grid_dist.y;
	}
}

/**
 * Cross Product here.
 * Since we use units of 1, only a division is needed in this case.
*/
static float	get_grid_increment_value(float ray_dir)
{
	if (ray_dir == 0)
		return (INFINITY);
	return (ft_fabs(1 / ray_dir));
}

static void	init_raycast_data(t_player *p, t_raycast *r, int x)
{
	float	x_relative_to_center_of_screen;

	r->ray_pos.x = (int)p->position.x;
	r->ray_pos.y = (int)p->position.y;
	x_relative_to_center_of_screen = 2 * x / (float)WIDTH - 1;
	r->ray_dir.x = p->delta.x + p->cam_plane.x * x_relative_to_center_of_screen;
	r->ray_dir.y = p->delta.y + p->cam_plane.y * x_relative_to_center_of_screen;
	r->grid_dist.x = get_grid_increment_value(r->ray_dir.x);
	r->grid_dist.y = get_grid_increment_value(r->ray_dir.y);
	get_initial_offset(p, r);
}

/**
 * Raycasting logic, drawing in this order:
 * - Background colors
 * - Floor / Ceiling textures
 * - Walls
 * - Assets
 * 
 * The ray_hits_opened_door variable is used to draw a door texture
 * and what's after it if the pixel is transparent.
 * 
 * The wall_perp_dist is stored in the z_buffer used to prevent assets
 * further than the walls to be drawn.
*/
void	raycast(void)
{
	t_cub		*cub;
	t_raycast	*r;
	int			x;

	cub = call_cub();
	r = &cub->raycast;
	if (BONUS)
		draw_floor_ceiling_textures(cub);
	x = 0;
	while (x < WIDTH)
	{
		r->ray_hits_opened_door = false;
		init_raycast_data(&cub->player, r, x);
		execute_dda_algo(&cub->raycast);
		draw_wall_stripe(r->ray_pos, &r->ray, x);
		if (r->ray_hits_opened_door)
			draw_wall_stripe(r->ray_pos_door, &r->ray_door, x);
		r->z_buffer[x] = r->ray.wall_perp_dist;
		x++;
	}
	if (BONUS)
		draw_assets(cub);
}
