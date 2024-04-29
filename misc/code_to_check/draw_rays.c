/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:17 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/29 11:27:07 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	it might be better to draw the player and the rays in full minimap instead ?

	
*/

# define FOV_COLOR	HEX_ORANGE

t_fpoint	cast_ray(t_fpoint origin, float angle)
{
	t_map	*map = get_map(call_cub()->current_level);
	t_fpoint	intersection = origin;
	float	step_x = cos(angle);
	float	step_y = sin(angle);

	while (map->map_array[(int)intersection.y][(int)intersection.x] != 1)
	{
		intersection.x += step_x;
		intersection.y += step_y;
	}
	return (intersection);
}

void	draw_fov(t_radar *radar, t_player *player)
{
	int		num_rays = 80;
	float	fov_angle = player->fov;

	float	ray_angle = player->angle - (fov_angle / 2);
	float	ray_angle_increment = fov_angle / num_rays;

	int		i = 0;
	while (i < num_rays)
	{
		t_fpoint	intersection = cast_ray(player->position, ray_angle);
		draw_line(radar->img, player->position, intersection, FOV_COLOR);
		ray_angle += ray_angle_increment;
		i++;
	}
}

t_fpoint	cast_ray(t_fpoint origin, float angle, t_radar *radar, t_minimap *mini)
{
	t_map		*map = get_map(call_cub()->current_level);
	t_fpoint	intersection = origin;
	float		step_x = cos(angle);
	float		step_y = sin(angle);

	while (map->map_array[(int)intersection.y][(int)intersection.x] != 1)
	{
		intersection.x += step_x;
		intersection.y += step_y;
	}

	// apply radar offset
	intersection.x = intersection.x * mini->tile_size + radar->offset.x;
	intersection.y = intersection.y * mini->tile_size + radar->offset.y;

	return (intersection);
}

void	draw_fov(t_radar *radar, t_player *player, t_minimap *mini)
{
	int		num_rays = 80;
	float	fov_angle = player->fov;

	float	ray_angle = player->angle - (fov_angle / 2);
	float	ray_angle_increment = fov_angle / num_rays;

	int		i = 0;
	while (i < num_rays)
	{
		t_fpoint	intersection = cast_ray(player->position, ray_angle, radar, mini);
		draw_line(radar->img, radar->center, intersection, FOV_COLOR);
		ray_angle += ray_angle_increment;
		i++;
	}
}
