/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:35:43 by oroy              #+#    #+#             */
/*   Updated: 2024/04/29 18:31:44 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_ray_bounds(t_cub *cub)
{
	cub->raycast.ray_dir_min.x = cub->player.delta.x - cub->player.cam_plane.x;
	cub->raycast.ray_dir_min.y = cub->player.delta.y - cub->player.cam_plane.y;
	cub->raycast.ray_dir_max.x = cub->player.delta.x + cub->player.cam_plane.x;
	cub->raycast.ray_dir_max.y = cub->player.delta.y + cub->player.cam_plane.y;
}

static void	set_floor_ceiling_textures(t_cub *cub, t_texture tex[4])
{
	t_map	*current_lvl;

	current_lvl = get_map(cub->current_level);
	tex[0] = get_texture_info(cub->elevator.texture[E_FLOOR]);
	tex[1] = get_texture_info(cub->elevator.texture[E_CEILING]);
	tex[2] = get_texture_info(current_lvl->floor_ceiling_img[FLOOR]);
	tex[3] = get_texture_info(current_lvl->floor_ceiling_img[CEILING]);
}

void	draw_floor_ceiling_textures(t_cub *cub)
{
	t_texture	tex[4];
	int			y;

	ft_memset(tex, 0, sizeof (t_texture) * 4);
	set_floor_ceiling_textures(cub, tex);
	get_ray_bounds(cub);
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		draw_floor_ceiling_row(tex, y);
		y++;
	}
}
