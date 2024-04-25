/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:14:10 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/25 16:03:45 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	init_player(t_map *map)
{
	t_player	player;

	player.position.x = map->starting_position.x + 0.5;
	player.position.y = map->starting_position.y + 0.5;
	player.speed = PLAYER_SPEED;
	player.turn_speed = PLAYER_TURN_SPEED;
	player.fov = PLAYER_FOV;
	player.angle = cardinal_to_radian(map->spawn_orientation);
	player.delta.x = cos(degree_to_radian(player.angle));
	player.delta.y = -sin(degree_to_radian(player.angle));
	player.cam_plane.x = -player.delta.y * player.fov;
	player.cam_plane.y = player.delta.x * player.fov;
	player.size = PLAYER_SIZE;
	player.color = PLAYER_COLOR;
	return (player);
}

/* ************************************************************************** */

static void	update_player_position(t_cub *cub)
{
	t_fpoint	speed;
	t_fpoint	*pos;

	pos = &cub->player.position;
	speed = get_velocity(&cub->player);
	if (cub->keys.up || cub->keys.w)
	{
		pos->x += get_move_value(pos->x + speed.x, pos->y, speed.x);
		pos->y += get_move_value(pos->x, pos->y + speed.y, speed.y);
	}
	if (cub->keys.a)
	{
		pos->x += get_move_value(pos->x + speed.y, pos->y, speed.y);
		pos->y -= get_move_value(pos->x, pos->y - speed.x, speed.x);
	}
	if (cub->keys.down || cub->keys.s)
	{
		pos->x -= get_move_value(pos->x - speed.x, pos->y, speed.x);
		pos->y -= get_move_value(pos->x, pos->y - speed.y, speed.y);
	}
	if (cub->keys.d)
	{
		pos->x -= get_move_value(pos->x - speed.y, pos->y, speed.y);
		pos->y += get_move_value(pos->x, pos->y + speed.x, speed.x);
	}
}

static void	update_player_direction(t_cub *cub)
{
	t_player	*player;

	player = &cub->player;
	if (cub->keys.right)
	{
		apply_rotation_matrix(&player->delta, player->turn_speed);
		apply_rotation_matrix(&player->cam_plane, player->turn_speed);
	}
	if (cub->keys.left)
	{
		apply_rotation_matrix(&player->delta, -player->turn_speed);
		apply_rotation_matrix(&player->cam_plane, -player->turn_speed);
	}
	if (cub->mouse.right)
	{
		apply_rotation_matrix(&player->delta, cub->mouse.rotate_x);
		apply_rotation_matrix(&player->cam_plane, cub->mouse.rotate_x);
		cub->mouse.right = OFF;
	}
	if (cub->mouse.left)
	{
		apply_rotation_matrix(&player->delta, -cub->mouse.rotate_x);
		apply_rotation_matrix(&player->cam_plane, -cub->mouse.rotate_x);
		cub->mouse.left = OFF;
	}
}

void	update_player(t_player *player)
{
	t_cub	*cub;

	cub = call_cub();
	if (player->speedup)
		player->speed = PLAYER_SPEED * 2;
	else
		player->speed = PLAYER_SPEED;
	update_player_position(cub);
	update_player_direction(cub);
}
