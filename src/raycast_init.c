/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:56:09 by oroy              #+#    #+#             */
/*   Updated: 2024/04/24 20:11:57 by cdumais          ###   ########.fr       */
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

static void	raycast_vertical(t_cub *cub)
{
	t_texture	tex[4];
	int			y;

	tex[0] = get_texture_floor_info(get_map(cub->current_level)->floor_ceiling_img[FLOOR]);
	tex[1] = get_texture_floor_info(get_map(cub->current_level)->floor_ceiling_img[CEILING]);
	tex[2] = get_texture_floor_info(cub->elevator.texture[E_FLOOR]);
	tex[3] = get_texture_floor_info(cub->elevator.texture[E_CEILING]);
	get_ray_bounds();
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		draw_ceiling_floor(tex, y);
		y++;
	}
}

void	raycast(void)
{
	t_cub		*cub;
	float		z_buffer[WIDTH];
	t_raycast	*r;
	int			x;

	cub = call_cub();
	x = 0;
	r = &cub->raycast;
	clear_img(cub->img);
	if (get_map(cub->current_level)->floor_ceiling_img[0] \
	&& !cub->keys.two)
		raycast_vertical(cub);
	while (x < WIDTH)
	{
		cub->elevator.door_open = false;

		init_raycast_data(&cub->player, r, x);
		execute_dda_algo(&cub->raycast);
		draw_wall_stripe(r->ray_pos, &r->ray, x);

		if (cub->elevator.door_open)
			draw_wall_stripe(r->ray_pos_door, &r->ray_door, x);
		
		z_buffer[x] = r->ray.wall_perp_dist;
		x++;
	}
	if (get_level(cub->current_level)->assets)
		draw_assets(z_buffer);
}
