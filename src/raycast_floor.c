/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:35:43 by oroy              #+#    #+#             */
/*   Updated: 2024/04/24 18:48:32 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	get_position_and_step(t_fpoint *pos, t_fpoint *step, int y)
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
	row_distance = center_of_screen / (float)y_relative_to_center;
	pos->x = cub->player.position.x + row_distance * r->ray_dir_min.x;
	pos->y = cub->player.position.y + row_distance * r->ray_dir_min.y;
	step->x = row_distance * (r->ray_dir_max.x - r->ray_dir_min.x) / WIDTH;
	step->y = row_distance * (r->ray_dir_max.y - r->ray_dir_min.y) / WIDTH;
	return (row_distance);
}

t_texture	get_texture_floor_info(mlx_image_t *texture)
{
	t_texture	tex;

	ft_memset(&tex, 0, sizeof (t_texture));
	tex.to_draw = texture;
	tex.width = (int)tex.to_draw->width;
	tex.height = (int)tex.to_draw->height;
	return (tex);
}

static void	draw_row_pixel(t_texture tex[4], t_fpoint pos, int x, int y, float distance)
// static void	draw_row_pixel(t_texture tex[4], t_fpoint pos, int x, int y)
{
	t_cub	*cub;
	int		color[2];
	// int		*color_ptrs[2] = {&color[FLOOR], &color[CEILING]};

	cub = call_cub();
	color[0] = get_pixel(tex[0].to_draw, tex[0].pixel.x, tex[0].pixel.y);
	color[1] = get_pixel(tex[1].to_draw, tex[1].pixel.x, tex[1].pixel.y);
	
	if ((int)pos.x == cub->elevator.position.x &&
		(int)pos.y == cub->elevator.position.y)
	{
		color[0] = get_pixel(tex[2].to_draw, tex[2].pixel.x, tex[2].pixel.y);
		color[1] = get_pixel(tex[3].to_draw, tex[3].pixel.x, tex[3].pixel.y);
	}
	else
	{
		color[0] = get_pixel(tex[0].to_draw, tex[0].pixel.x, tex[0].pixel.y);
		color[1] = get_pixel(tex[1].to_draw, tex[1].pixel.x, tex[1].pixel.y);
	}
	// floor_ceiling_vfx(color_ptrs, distance);
	
	if (cub->vfx.shadow.enabled)
	{
		color[0] = shadow_effect(color[0], distance, 0.0f, 3.0f);
		color[1] = shadow_effect(color[1], distance, 0.0f, 3.0f);
	}
	draw_pixel(cub->img, x, y, color[0]);
	draw_pixel(cub->img, x, HEIGHT - y - 1, color[1]);
}

void	draw_ceiling_floor(t_texture tex[4], int y)
{
	// t_texture	tex[4];
	t_fpoint	pos;
	t_fpoint	step;
	float		distance;
	int			x;

	x = 0;
	// tex[0] = get_texture_info(cub->texture[F]);
	// tex[0] = get_texture_info(get_map(cub->current_level)->floor_ceiling_img[FLOOR]);
	// // tex[1] = get_texture_info(cub->texture[C]);
	// tex[1] = get_texture_info(get_map(cub->current_level)->floor_ceiling_img[CEILING]);
	
	// tex[2] = get_texture_info(cub->elevator.texture[E_FLOOR]);
	// tex[3] = get_texture_info(cub->elevator.texture[E_CEILING]);
	// get_ray_bounds(cub);
	distance = get_position_and_step(&pos, &step, y);
	while (x < WIDTH)
	{
		tex[0].pixel = update_texture_position(tex[0], pos);
		tex[1].pixel = update_texture_position(tex[1], pos);
		tex[2].pixel = update_texture_position(tex[2], pos);
		tex[3].pixel = update_texture_position(tex[3], pos);
		pos.x += step.x;
		pos.y += step.y;
		draw_row_pixel(tex, pos, x, y, distance);
		// draw_row_pixel(tex, pos, x, y);
		x++;
	}
}

// void	draw_ceiling_floor(t_cub *cub, int y)
// {
// 	t_point		tex_pos_f;
// 	t_point		tex_pos_c;
// 	t_point		tex_size_f;
// 	t_point		tex_size_c;
// 	t_fpoint	pos;
// 	t_fpoint	step;
// 	// float		distance;
// 	int			color[2];
// 	// int			*color_ptrs[2] = {&color[FLOOR], &color[CEILING]};
// 	int			x;

// 	x = 0;
// 	tex_size_f = (t_point){cub->texture[F]->width, cub->texture[F]->height};
// 	tex_size_c = (t_point){cub->texture[C]->width, cub->texture[C]->height};
// 	get_ray_bounds(cub);
// 	// distance = get_position_and_step(cub, &pos, &step, y);
// 	get_position_and_step(&pos, &step, y);
// 	while (x < WIDTH)
// 	{
// 		tex_pos_f.x = ft_abs((int)(tex_size_f.x * (pos.x - (int) pos.x)));
// 		tex_pos_f.y = ft_abs((int)(tex_size_f.y * (pos.y - (int) pos.y)));
// 		tex_pos_c.x = ft_abs((int)(tex_size_c.x * (pos.x - (int) pos.x)));
// 		tex_pos_c.y = ft_abs((int)(tex_size_c.y * (pos.y - (int) pos.y)));
// 		pos.x += step.x;
// 		pos.y += step.y;
// 		if ((int)pos.x == cub->elevator.position.x && (int)pos.y == cub->elevator.position.y)
// 		{
// 			color[FLOOR] = get_pixel(cub->elevator.texture[E_FLOOR], tex_pos_f.x, tex_pos_f.y);
// 			color[CEILING] = get_pixel(cub->elevator.texture[E_CEILING], tex_pos_f.x, tex_pos_f.y);
// 		}
// 		else
// 		{
// 			color[FLOOR] = get_pixel(cub->texture[F], tex_pos_f.x, tex_pos_f.y);
// 			color[CEILING] = get_pixel(cub->texture[C], tex_pos_c.x, tex_pos_c.y);
// 		}
// 		// floor_ceiling_vfx(color_ptrs, distance);

// 		draw_pixel(cub->img, x, y, color[FLOOR]);
// 		draw_pixel(cub->img, x, HEIGHT - y - 1, color[CEILING]);
// 		x++;
// 	}
// }
