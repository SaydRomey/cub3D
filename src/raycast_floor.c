/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:35:43 by oroy              #+#    #+#             */
/*   Updated: 2024/03/16 20:12:56 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	get_position_and_step(t_cub *cub, t_fpoint *pos, t_fpoint *step, int y)
{
	int			y_relative_to_center;
	int			center_of_screen;
	float		row_distance;
	t_raycast	*r;

	r = &cub->raycast;
	center_of_screen = HEIGHT / 2;
	y_relative_to_center = y - center_of_screen;
	row_distance = center_of_screen / (float)y_relative_to_center;
	pos->x = cub->player.position.x + row_distance * r->ray_dir_min.x;
	pos->y = cub->player.position.y + row_distance * r->ray_dir_min.y;
	step->x = row_distance * (r->ray_dir_max.x - r->ray_dir_min.x) / WIDTH;
	step->y = row_distance * (r->ray_dir_max.y - r->ray_dir_min.y) / WIDTH;
	return (row_distance);
}

static void	get_ray_bounds(t_cub *cub)
{
	cub->raycast.ray_dir_min.x = cub->player.delta.x - cub->player.cam_plane.x;
	cub->raycast.ray_dir_min.y = cub->player.delta.y - cub->player.cam_plane.y;
	cub->raycast.ray_dir_max.x = cub->player.delta.x + cub->player.cam_plane.x;
	cub->raycast.ray_dir_max.y = cub->player.delta.y + cub->player.cam_plane.y;
}

void	draw_ceiling_floor(t_cub *cub, int y)
{
	t_point		tex_pos;
	t_fpoint	pos;
	t_fpoint	step;
	// float		distance;
	int			color[2];
	// int			*color_ptrs[2] = {&color[FLOOR], &color[CEILING]};
	int			x;

	x = 0;
	get_ray_bounds(cub);
	// distance = get_position_and_step(cub, &pos, &step, y);
	get_position_and_step(cub, &pos, &step, y);
	while (x < WIDTH)
	{
		tex_pos.x = ft_abs((int)(TEX_WIDTH * (pos.x - (int)pos.x)));
		tex_pos.y = ft_abs((int)(TEX_HEIGHT * (pos.y - (int)pos.y)));
		pos.x += step.x;
		pos.y += step.y;
		color[FLOOR] = get_pixel(cub->texture[F], tex_pos.x, tex_pos.y);
		color[CEILING] = get_pixel(cub->texture[C], tex_pos.x, tex_pos.y);

		// floor_ceiling_vfx(color_ptrs, distance);

		draw_pixel(cub->img, x, y, color[FLOOR]);
		draw_pixel(cub->img, x, HEIGHT - y - 1, color[CEILING]);
		x++;
	}
}
