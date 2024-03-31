/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:56:09 by oroy              #+#    #+#             */
/*   Updated: 2024/03/29 13:42:47 by oroy             ###   ########.fr       */
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

void	raycast(t_cub *cub)
{
	t_raycast	*r;
	// float		z_buffer[WIDTH];
	int			x;
	int			y;

	// if (cub->vfx.textures_enabled == false)
	// {
	// 	draw_ceiling(cub->img, cub->map->ceiling_color);
	// 	draw_floor(cub->img, cub->map->floor_color);
	// }
	x = 0;
	y = HEIGHT / 2;
	r = &cub->raycast;
	clear_img(cub->img);
	while (y < HEIGHT)
	{
		draw_ceiling_floor(cub, y);
		y++;
	}
	while (x < WIDTH)
	{
		cub->elevator.door_open = false;
		init_raycast_data(&cub->player, r, x);
		execute_dda_algo(cub, &cub->raycast);
		draw_wall_stripe(cub, r->ray_pos, &r->ray, x);
		if (cub->elevator.door_open)
			draw_wall_stripe(cub, r->ray_pos_door, &r->ray_door, x);
		// z_buffer[x] = cub->raycast.ray.wall_perp_dist;
		x++;
	}
	// draw_assets(cub, z_buffer);
}
