/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_fov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 03:11:25 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/02 03:14:52 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_wall(int x, int y, t_map *map)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (true);
	return (map->map_array[y][x] == WALL);
}

static t_fpoint	cast_ray_until_wall(t_fpoint map_origin, t_fpoint direction)
{
	t_map		*map;
	t_fpoint	current;

	map = get_map(call_cub()->current_level);
	current = map_origin;
	while (!is_wall((int)current.x, (int)current.y, map))
	{
		current.x += direction.x;
		current.y += direction.y;
	}
	return (current);
}

static t_fpoint	map_to_minimap(t_fpoint map_point, void *param)
{
	t_minimap	*mini;
	t_fpoint	minimap_point;
	
	mini = (t_minimap *)param;
	minimap_point.x = map_point.x * mini->tile_size + mini->offset.x;
	minimap_point.y = map_point.y * mini->tile_size + mini->offset.y;
	return (minimap_point);
}

static t_fpoint	cast_ray_with_rotation(t_fpoint map_origin, t_fpoint direction, \
float angle, t_minimap *mini)
{
	t_fpoint	rotated_direction;
	t_fpoint	ray_tip;
	
	rotated_direction = rotate_vector(direction, angle);
	rotated_direction.x *= 0.01;
	rotated_direction.y *= 0.01;
	ray_tip = cast_ray_until_wall(map_origin, rotated_direction);
	return (map_to_minimap(ray_tip, mini));
}

void	draw_fov(t_minimap *mini, t_player *player)
{
	float		half_fov;
	float		angle_increment;
	t_fpoint	player_pos;
	float		angle;
	t_fpoint	ray;
	
	half_fov = player->fov / 2;
	angle_increment = player->fov / 20;
	player_pos = map_to_minimap(player->position, mini);
	angle = -half_fov;
	while (angle <= half_fov)
	{
		ray = cast_ray_with_rotation(player->position, player->delta, \
		angle, mini);
		draw_line(mini->img, player_pos, ray, FOV_COLOR);
		angle += angle_increment;
	}
}
