/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:52:54 by oroy              #+#    #+#             */
/*   Updated: 2024/04/24 20:13:20 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_image_t	*get_tex(int x, int y, mlx_image_t *tex)
{
	if (check_hit(x, y) == ELEVATOR)
		return (call_cub()->elevator.texture[E_WALL]);
	return (tex);
}

static mlx_image_t	*get_texture_to_draw(t_cub *cub, t_point ray_pos, bool side)
{
	t_map	*map;
	int		idx;

	map = get_map(cub->current_level);
	
	if (check_hit(ray_pos.x, ray_pos.y) == ELEVATOR)
	{
		idx = cub->elevator.door_animation.current_frame;
		return (cub->elevator.door_animation.frames[idx]);
	}
	if (side == 1 && cub->raycast.ray_dir.y < 0)
		return (get_tex(ray_pos.x, ray_pos.y + 1, map->wall_textures_img[NO]));
	if (side == 1 && cub->raycast.ray_dir.y > 0)
		return (get_tex(ray_pos.x, ray_pos.y - 1, map->wall_textures_img[SO]));
	if (side == 0 && cub->raycast.ray_dir.x < 0)
		return (get_tex(ray_pos.x + 1, ray_pos.y, map->wall_textures_img[WE]));
	if (side == 0 && cub->raycast.ray_dir.x > 0)
		return (get_tex(ray_pos.x - 1, ray_pos.y, map->wall_textures_img[EA]));
	return (NULL);
}

static t_texture	get_texture_info(float whp, t_point ray_pos, bool side)
{
	t_cub		*cub;
	t_texture	tex;

	cub = call_cub();
	tex.to_draw = get_texture_to_draw(cub, ray_pos, side);
	tex.width = (int)tex.to_draw->width;
	tex.height = (int)tex.to_draw->height;
	tex.pixel.x = (int)(whp * tex.width);
	if ((side == 0 && cub->raycast.ray_dir.x < 0) ||
		(side == 1 && cub->raycast.ray_dir.y > 0))
		tex.pixel.x = tex.width - tex.pixel.x - 1;
	tex.pixel.y = 0;
	return (tex);
}

// static t_line	get_stripe_data(float wall_perp_dist)
// {
// 	t_line	line;

// 	line.height = (int)(HEIGHT / wall_perp_dist);
// 	line.start = (HEIGHT / 2) - (line.height / 2);
// 	if (line.start < 0)
// 		line.start = 0;
// 	line.end = (HEIGHT / 2) + (line.height / 2);
// 	if (line.end >= HEIGHT)
// 		line.end = HEIGHT - 1;
// 	return (line);
// }

void	draw_wall_stripe(t_point ray_pos, t_render *r, int x)
{
	t_cub			*cub;
	t_texture		tex;
	t_line			line;
	float		distance;
	int				color;
	int				y;

	cub = call_cub();
	line = get_stripe_data(r->wall_perp_dist, HEIGHT / 2, HEIGHT);
	tex = get_texture_info(r->wall_hit_pos, ray_pos, r->side);
	tex.step_y = tex.to_draw->height / (float) line.size;
	tex.pos_y = (line.start - (HEIGHT / 2) + (line.size / 2)) * tex.step_y;
	y = line.start;
	while (y <= line.end)
	{
		tex.pixel.y = (int) tex.pos_y & (tex.width - 1);
		tex.pos_y += tex.step_y;
		color = get_pixel(tex.to_draw, tex.pixel.x, tex.pixel.y);
		
		distance = cub->raycast.ray.wall_perp_dist;
		// wall_vfx(&color, distance, (float)tex.pos_y);
		
		if (cub->vfx.shadow.enabled)
		{
			color = shadow_effect(color, distance, 0.0f, 5.0f);
		}		
		if (get_alpha(color) == 255)
			draw_pixel(cub->img, x, y, color);
		y++;
	}
}
