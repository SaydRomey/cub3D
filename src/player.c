/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:14:10 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/14 19:39:09 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	spawning_orientation(char direction)
{
	if (direction == 'N')
		return (90);
	if (direction == 'S')
		return (270);
	if (direction == 'E')
		return (0);
	if (direction == 'W')
		return (180);
	return (-1);
}

t_player	init_player(t_scene *scene)
{
	t_player	player;
	
	player.position.x = scene->starting_position.x + 0.5;
	player.position.y = scene->starting_position.y + 0.5;
	player.angle = spawning_orientation(scene->spawn_orientation);
	player.fov = PLAYER_FOV;
	player.delta.x = cos(degree_to_radian(player.angle));
	player.delta.y = -sin(degree_to_radian(player.angle));
	player.cam_plane.x = -player.delta.y * player.fov;
	player.cam_plane.y = player.delta.x * player.fov;
	player.speed = PLAYER_SPEED;
	player.turn_speed = PLAYER_TURN_SPEED;
	// 
	player.size = PLAYER_SIZE;
	player.color = 0xFF00FFFF;
	// 
	// player.respawn = &player; //need to fix this to create a full copy of player instead..
	return (player);
}

/*
use t_map instead? **

*/
static float	get_move_value(int x, int y, float rtn_value)
{
	if (!check_hit(x, y))
		return (rtn_value);
	return (0);
}

static t_fpoint	get_velocity(t_cub *cub) //change to t_player?
{
	t_fpoint	velocity;

	velocity.x = cub->player.delta.x * cub->player.speed;
	velocity.y = cub->player.delta.y * cub->player.speed;
	return (velocity);
}

void	update_player_position(t_cub *cub) //tmp cannot move if leftcontrol is pressed
{
	t_fpoint	velocity;
	t_fpoint	*pos;

	pos = &cub->player.position;
	velocity = get_velocity(cub);
	if (cub->keys.w || (cub->keys.up && !cub->keys.leftcontrol))
	{
		pos->x += get_move_value(pos->x + velocity.x, pos->y, velocity.x);
		pos->y += get_move_value(pos->x, pos->y + velocity.y, velocity.y);
	}
	if (cub->keys.a)
	{
		pos->x += get_move_value(pos->x + velocity.y, pos->y, velocity.y);
		pos->y -= get_move_value(pos->x, pos->y - velocity.x, velocity.x);
	}
	if (cub->keys.s || (cub->keys.down && !cub->keys.leftcontrol))
	{
		pos->x -= get_move_value(pos->x - velocity.x, pos->y, velocity.x);
		pos->y -= get_move_value(pos->x, pos->y - velocity.y, velocity.y);
	}
	if (cub->keys.d)
	{
		pos->x -= get_move_value(pos->x - velocity.y, pos->y, velocity.y);
		pos->y += get_move_value(pos->x, pos->y + velocity.x, velocity.x);
	}
}

static void	apply_rotation_matrix(t_fpoint *src, float turn_speed)
{
	t_fpoint	tmp;

	tmp.x = src->x;
	tmp.y = src->y;
	src->x = tmp.x * cos(turn_speed) - tmp.y * sin(turn_speed);
	src->y = tmp.x * sin(turn_speed) + tmp.y * cos(turn_speed);
}

void	update_player_direction(t_cub *cub)
{
	t_player	*player;

	player = &cub->player;
	if (cub->keys.right && !cub->keys.leftcontrol)
	{
		apply_rotation_matrix(&player->delta, player->turn_speed);
		apply_rotation_matrix(&player->cam_plane, player->turn_speed);
	}
	if (cub->keys.left && !cub->keys.leftcontrol)
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

static void	update_player_stats(t_player *player, t_keys *keys)
{
	player->speedup = keys->leftshift;

	if (player->speedup)
		player->speed = PLAYER_SPEED * 2;
	else
		player->speed = PLAYER_SPEED;
}

void	update_player(t_cub *cub)
{
	t_player	*player;

	player = &cub->player;
	// if (cub->keys.backspace)
	// 	*player = *player->respawn; //needs a fixing
	// 
	update_player_stats(player, &cub->keys); //test, might use this for inventory ?
	// 
	update_player_position(cub);
	update_player_direction(cub);
}
