/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:35:43 by oroy              #+#    #+#             */
/*   Updated: 2024/04/24 00:27:18 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	get_initial_pos_and_step(t_fpoint *pos, t_fpoint *step, int y)
{
	int			y_relative_to_center;
	int			center_of_screen;
	float		row_distance;
	t_cub		*cub;
	t_raycast	*r;

	cub = call_cub();
	r = &cub->raycast;
	center_of_screen = HEIGHT / 2;
	y_relative_to_center = y - center_of_screen;
	if (y_relative_to_center == 0)
		row_distance = INFINITY;
	else
		row_distance = center_of_screen / (float)y_relative_to_center;
	//
	// Get leftmost position of row
	pos->x = cub->player.position.x + row_distance * r->ray_dir_min.x;
	pos->y = cub->player.position.y + row_distance * r->ray_dir_min.y;
	//
	// Get increment value in grid space from left to right of row
	step->x = row_distance * (r->ray_dir_max.x - r->ray_dir_min.x) / WIDTH;
	step->y = row_distance * (r->ray_dir_max.y - r->ray_dir_min.y) / WIDTH;
	//
	// Return distance for vfx
	return (row_distance);
}

static void	draw_row_pixel(t_texture tex[2], float distance, int x, int y)
{
	t_cub	*cub;
	int		color[2];

	cub = call_cub();
	color[0] = get_pixel(tex[0].to_draw, tex[0].pixel.x, tex[0].pixel.y);
	color[1] = get_pixel(tex[1].to_draw, tex[1].pixel.x, tex[1].pixel.y);
	if (cub->vfx.shadow.enabled)
	{
		color[0] = shadow_effect(color[0], distance, 0.0f, 3.0f);
		color[1] = shadow_effect(color[1], distance, 0.0f, 3.0f);
	}
	if (get_alpha(color[0]) == 255)
		draw_pixel(cub->img, x, y, color[0]);
	if (get_alpha(color[1]) == 255)
		draw_pixel(cub->img, x, HEIGHT - y - 1, color[1]);
}

static void	draw_row(t_texture tex[4], int y)
{
	float		distance;
	t_fpoint	pos;
	t_fpoint	step;
	int			x;

	x = 0;
	distance = get_initial_pos_and_step(&pos, &step, y);
	while (x < WIDTH)
	{
		if (position_is_elevator(pos.x, pos.y))
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

static void	get_ray_bounds(t_cub *cub)
{
	cub->raycast.ray_dir_min.x = cub->player.delta.x - cub->player.cam_plane.x;
	cub->raycast.ray_dir_min.y = cub->player.delta.y - cub->player.cam_plane.y;
	cub->raycast.ray_dir_max.x = cub->player.delta.x + cub->player.cam_plane.x;
	cub->raycast.ray_dir_max.y = cub->player.delta.y + cub->player.cam_plane.y;
}

t_texture	get_texture_floor_info(mlx_image_t *texture)
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

static void	set_floor_ceiling_textures(t_cub *cub, t_texture tex[4])
{
	t_map	*current_lvl;

	current_lvl = get_map(cub->current_level);
	tex[0] = get_texture_floor_info(cub->elevator.texture[E_FLOOR]);
	tex[1] = get_texture_floor_info(cub->elevator.texture[E_CEILING]);
	tex[2] = get_texture_floor_info(current_lvl->floor_ceiling_img[FLOOR]);
	tex[3] = get_texture_floor_info(current_lvl->floor_ceiling_img[CEILING]);
}

void	draw_floor_ceiling(t_cub *cub)
{
	t_texture	tex[4];
	int			y;

	ft_memset(tex, 0, sizeof (t_texture) * 4);
	set_floor_ceiling_textures(cub, tex);
	get_ray_bounds(cub);
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		draw_row(tex, y);
		y++;
	}
}
