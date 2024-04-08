/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:52:54 by oroy              #+#    #+#             */
/*   Updated: 2024/04/08 14:46:56 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_image_t	*get_tex(int x, int y, mlx_image_t *tex)
{
	(void)x; //tmp
	(void)y; //tmp

	
	// if (check_hit(x, y) == ELEVATOR)
	// 	return (call_cub()->elevator.texture[E_WALL]);
	return (tex);
}

static mlx_image_t	*get_texture_to_draw(t_cub *cub, t_point ray_pos, bool side)
{
	t_map	*map;
	// int		idx;

	// map = cub->map;
	map = get_map(cub->current_level);
	
	// if (check_hit(ray_pos.x, ray_pos.y) == ELEVATOR)
	// {
	// 	idx = cub->elevator.door_animation.current_frame;
	// 	return (cub->elevator.door_animation.frames[idx]);
	// }
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

	// (void)whp;
	// (void)ray_pos;
	// (void)side;


	cub = call_cub();
	
	// ft_memset(&tex, 0, sizeof(t_texture)); //? does this fix the segfault ?
	
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

static t_line	get_stripe_data(float wall_perp_dist)
{
	t_line	line;

	line.height = (int)(HEIGHT / wall_perp_dist);
	line.start = (HEIGHT / 2) - (line.height / 2);
	if (line.start < 0)
		line.start = 0;
	line.end = (HEIGHT / 2) + (line.height / 2);
	if (line.end >= HEIGHT)
		line.end = HEIGHT - 1;
	return (line);
}

void	draw_wall_stripe(t_cub *cub, t_point ray_pos, t_render *r, int x)
{
	t_texture		tex;
	t_line			line;
	// float		distance;
	int				color;
	int				y;

	(void)cub;
	// (void)ray_pos;
	// (void)x;

	line = get_stripe_data(r->wall_perp_dist);
	tex = get_texture_info(r->wall_hit_pos, ray_pos, r->side);
	tex.step_y = tex.to_draw->height / (float) line.height;
	tex.pos_y = (line.start - (HEIGHT / 2) + (line.height / 2)) * tex.step_y;
	y = line.start;
	while (y <= line.end)
	{
		tex.pixel.y = (int) tex.pos_y & (tex.width - 1);
		tex.pos_y += tex.step_y;
		color = get_pixel(tex.to_draw, tex.pixel.x, tex.pixel.y);
		
	// 	// distance = cub->raycast.wall_perp_dist;
	// 	// wall_vfx(&color, distance, (float)tex.pos_y);
		
		if (get_alpha(color) == 255)
			draw_pixel(cub->img, x, y, color);
		y++;
	}
}

// static float	ft_percent(float num, float total)
// {
//     if (total == 0)
//         return (0);
//     return ((num / total) * 100);
// }

// static float	ft_lerp(float a, float b, float t)
// {
//     return ((1 - t) * a + t * b);
// }

// static float	ft_fclamp(float value, float min, float max)
// {
//     return (ft_fmax(ft_fmin(value, max), min));
// }

// void	draw_wall_stripe(t_cub *cub, int x)
// {
// 	t_texture	tex;
// 	t_line		line;
// 	int			color;
// 	float		dist;
// 	int			y;

// 	printf ("%f\n", cub->raycast.wall_perp_dist);
// 	line = get_stripe_data(cub->raycast.wall_perp_dist);
// 	tex = get_texture_info(cub, &line);
// 	y = line.start;
// 	dist = ft_fclamp(cub->raycast.wall_perp_dist, 0, 5) / 5;
// 	while (y <= line.end)
// 	{
// 		// Is Bitwise AND really necessary here ?
// 		tex.pixel.y = (int) tex.pos_y & (TEX_HEIGHT - 1);
// 		tex.pos_y += tex.step_y;
// 		color = get_pixel(tex.to_draw, tex.pixel.x, tex.pixel.y);
// 		draw_pixel(cub->img, x, y, color * dist);
// 		y++;
// 	}
// }
