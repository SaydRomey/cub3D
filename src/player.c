/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:14:10 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/15 22:06:34 by oroy             ###   ########.fr       */
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
	// 
	player.size = PLAYER_SIZE;
	player.color = 0xFF00FFFF;
	// 
	cproof("***** player init *****", MAGENTA);
	return (player);	
}

t_player	warp_player(t_player old_player, t_level *lvl, t_level *next_lvl)
{
	t_player	player;
	t_fpoint	pos;
	int			rotation;

	player = old_player;
	pos.x = player.position.x - lvl->elevator_position.x;
	pos.y = player.position.y - lvl->elevator_position.y;
	rotation = next_lvl->elevator_orientation - lvl->elevator_orientation;
	if (rotation)
	{
		pos = rotate_vector_position(pos, rotation);
		player.delta = rotate_vector_delta(player.delta, -rotation);
		player.cam_plane.x = -player.delta.y * player.fov;
		player.cam_plane.y = player.delta.x * player.fov;
	}
	player.position.x = next_lvl->elevator_position.x + pos.x;
	player.position.y = next_lvl->elevator_position.y + pos.y;
	return (player);
}

static t_fpoint	get_velocity(t_cub *cub)
{
	t_fpoint	velocity;

	velocity.x = cub->player.delta.x * cub->player.speed;
	velocity.y = cub->player.delta.y * cub->player.speed;
	return (velocity);
}

static float	get_move_value(t_cub *cub, int x, int y, float rtn_value)
{
	int	tile;
	
	tile = check_hit(x, y); //next step of player

	// if next step is elevator and door is closed and we are not inside
	if (tile == 3 && cub->elevator.door == CLOSE
		&& !((int) cub->player.position.x == cub->elevator.position.x
		&& (int) cub->player.position.y == cub->elevator.position.y))
		return (0);
		
	// if next step is walkable and door is closed and we are inside
	if (tile == 0 && cub->elevator.door == CLOSE
		&& (int) cub->player.position.x == cub->elevator.position.x
		&& (int) cub->player.position.y == cub->elevator.position.y)
		return (0);
	
	if (tile == 1)
		return (0);
	return (rtn_value);
}

void	update_player_position(t_cub *cub)
{
	t_fpoint	speed;
	t_fpoint	*pos;

	pos = &cub->player.position;
	speed = get_velocity(cub);
	if (cub->keys.up || cub->keys.w)
	{
		pos->x += get_move_value(cub, pos->x + speed.x, pos->y, speed.x);
		pos->y += get_move_value(cub, pos->x, pos->y + speed.y, speed.y);
	}
	if (cub->keys.a)
	{
		pos->x += get_move_value(cub, pos->x + speed.y, pos->y, speed.y);
		pos->y -= get_move_value(cub, pos->x, pos->y - speed.x, speed.x);
	}
	if (cub->keys.down || cub->keys.s)
	{
		pos->x -= get_move_value(cub, pos->x - speed.x, pos->y, speed.x);
		pos->y -= get_move_value(cub, pos->x, pos->y - speed.y, speed.y);
	}
	if (cub->keys.d)
	{
		pos->x -= get_move_value(cub, pos->x - speed.y, pos->y, speed.y);
		pos->y += get_move_value(cub, pos->x, pos->y + speed.x, speed.x);
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
	
	update_player_stats(player, &cub->keys); //test, might use this for inventory ?
	
	update_player_position(cub);
	update_player_direction(cub);

	// draw miniplayer ..?

}
