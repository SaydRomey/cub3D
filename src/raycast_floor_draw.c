/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:43:59 by oroy              #+#    #+#             */
/*   Updated: 2024/04/29 19:07:55 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	get_row_distance(t_raycast *r, int y)
{
	int		y_relative_to_center;
	int		center_of_screen;
	float	row_distance;

	center_of_screen = HEIGHT / 2;
	row_distance = r->row_distance[y - center_of_screen];
	if (row_distance == 0)
	{
		y_relative_to_center = y - center_of_screen;
		if (y_relative_to_center == 0)
			row_distance = INFINITY;
		else
			row_distance = center_of_screen / (float)y_relative_to_center;
	}
	return (row_distance);
}

/**
 * @param pos Initial position of the row (leftmost position)
 * @param step Increment value in grid space from left to right
 * @param y Vertical position of the row in screen space
 * 
 * @return row_distance is returned to apply vfx on the pixels
*/
static float	get_initial_pos_and_step(t_fpoint *pos, t_fpoint *step, int y)
{
	float		row_distance;
	t_cub		*cub;
	t_raycast	*r;

	cub = call_cub();
	r = &cub->raycast;
	row_distance = get_row_distance(r, y);
	pos->x = cub->player.position.x + row_distance * r->ray_dir_min.x;
	pos->y = cub->player.position.y + row_distance * r->ray_dir_min.y;
	step->x = row_distance * (r->ray_dir_max.x - r->ray_dir_min.x) / WIDTH;
	step->y = row_distance * (r->ray_dir_max.y - r->ray_dir_min.y) / WIDTH;
	return (row_distance);
}

/**
 * Get pixel coordinates according to position in grid.
 * Getting the absolute value (ft_abs) is necessary
 * since there are no negative values in texture.
*/
static t_point	get_pixel_in_texture(t_texture tex, t_fpoint pos)
{
	t_point	tex_pos;

	tex_pos.x = ft_abs((int)(tex.width * (pos.x - (int) pos.x)));
	tex_pos.y = ft_abs((int)(tex.height * (pos.y - (int) pos.y)));
	return (tex_pos);
}

static void	draw_row_pixel(t_texture tex[2], float distance, int x, int y)
{
	t_cub	*cub;
	int		color[2];

	cub = call_cub();
	color[0] = get_pixel(tex[0].to_draw, tex[0].pixel.x, tex[0].pixel.y);
	color[1] = get_pixel(tex[1].to_draw, tex[1].pixel.x, tex[1].pixel.y);
	if (cub->vfx.shadow_enabled)
	{
		color[0] = shadow_effect(color[0], distance, 0.0f, 3.0f);
		color[1] = shadow_effect(color[1], distance, 0.0f, 3.0f);
	}
	if (get_alpha(color[0]) == 255)
		draw_pixel(cub->img, x, y, color[0]);
	if (get_alpha(color[1]) == 255)
		draw_pixel(cub->img, x, HEIGHT - y - 1, color[1]);
}

void	draw_floor_ceiling_row(t_texture tex[4], int y)
{
	float		distance;
	t_fpoint	pos;
	t_fpoint	step;
	int			x;

	x = 0;
	distance = get_initial_pos_and_step(&pos, &step, y);
	while (x < WIDTH)
	{
		if (check_hit(pos.x, pos.y) == ELEVATOR)
		{
			tex[0].pixel = get_pixel_in_texture(tex[0], pos);
			tex[1].pixel = get_pixel_in_texture(tex[1], pos);
			draw_row_pixel(tex, distance, x, y);
		}
		else
		{
			tex[2].pixel = get_pixel_in_texture(tex[2], pos);
			tex[3].pixel = get_pixel_in_texture(tex[3], pos);
			draw_row_pixel(&tex[2], distance, x, y);
		}
		pos.x += step.x;
		pos.y += step.y;
		x++;
	}
}
