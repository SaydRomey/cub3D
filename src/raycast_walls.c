/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:52:54 by oroy              #+#    #+#             */
/*   Updated: 2024/03/06 16:25:52 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_image_t	*get_texture_to_draw(t_cub *cub)
{
	if (check_hit2(cub->raycast.ray_pos.x, cub->raycast.ray_pos.y, cub->map.map_array) == 2)
		return (cub->texture[I]);
	if (cub->raycast.side == 1 && cub->raycast.ray_dir.y < 0)
		return (cub->texture[NO]);
	if (cub->raycast.side == 1 && cub->raycast.ray_dir.y > 0)
		return (cub->texture[SO]);
	if (cub->raycast.side == 0 && cub->raycast.ray_dir.x < 0)
		return (cub->texture[WE]);
	if (cub->raycast.side == 0 && cub->raycast.ray_dir.x > 0)
		return (cub->texture[EA]);
	return (NULL);
}

static int	get_x_coordinate(t_raycast *r)
{
	int	x;

	x = (int)(r->wall_hit_pos * TEX_WIDTH);
	if ((r->side == 0 && r->ray_dir.x < 0)
		|| (r->side == 1 && r->ray_dir.y > 0))
		x = TEX_WIDTH - x - 1;
	return (x);
}

static t_texture	get_texture_info(t_cub *cub, t_line *line)
{
	t_texture	tex;

	tex.pixel.y = 0;
	tex.pixel.x = get_x_coordinate(&cub->raycast);
	tex.step_y = TEX_HEIGHT / (float) line->height;
	tex.pos_y = (line->start - (HEIGHT / 2) + (line->height / 2)) * tex.step_y;
	tex.to_draw = get_texture_to_draw(cub);
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

void	draw_wall_stripe(t_cub *cub, int x)
{
	t_texture	tex;
	t_line		line;
	int			color;
	int			y;

	line = get_stripe_data(cub->raycast.wall_perp_dist);
	tex = get_texture_info(cub, &line);
	y = line.start;
	while (y <= line.end)
	{
		// Is Bitwise AND really necessary here ?
		tex.pixel.y = (int) tex.pos_y & (TEX_HEIGHT - 1);
		tex.pos_y += tex.step_y;
		color = get_pixel(tex.to_draw, tex.pixel.x, tex.pixel.y);
		draw_pixel(cub->img, x, y, color);
		y++;
	}
}
