/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:35:43 by oroy              #+#    #+#             */
/*   Updated: 2024/03/14 13:50:26 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_position_and_step(t_cub *cub, t_point *pos, t_point *step, int y)
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
	int				tex_pos[2];
	int				color[2];
	t_point			pos;
	t_point			step;
	int				x;

	x = 0;
	get_ray_bounds(cub);
	get_position_and_step(cub, &pos, &step, y);
	while (x < WIDTH)
	{
		tex_pos[0] = ft_abs((int)(TEX_WIDTH * (pos.x - (int)pos.x)));
		tex_pos[1] = ft_abs((int)(TEX_HEIGHT * (pos.y - (int)pos.y)));
		pos.x += step.x;
		pos.y += step.y;
		color[FLOOR] = get_pixel(cub->texture[F], tex_pos[0], tex_pos[1]);
		color[CEILING] = get_pixel(cub->texture[C], tex_pos[0], tex_pos[1]);

		// floor_ceiling_vfx(&color, );

		draw_pixel(cub->img, x, y, color[FLOOR]);
		draw_pixel(cub->img, x, HEIGHT - y - 1, color[CEILING]);
		x++;
	}
}
