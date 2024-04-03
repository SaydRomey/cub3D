// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   player.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/02/21 13:14:10 by cdumais           #+#    #+#             */
// /*   Updated: 2024/03/22 19:17:56 by oroy             ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3d.h"

// static int	spawning_orientation(char direction)
// {
// 	if (direction == 'N')
// 		return (90);
// 	if (direction == 'S')
// 		return (270);
// 	if (direction == 'E')
// 		return (0);
// 	if (direction == 'W')
// 		return (180);
// 	return (-1);
// }

// t_player	init_player(t_scene *scene)
// {
// 	t_player	player;
	
// 	player.position.x = scene->starting_position.x + 0.5;
// 	player.position.y = scene->starting_position.y + 0.5;
// 	player.angle = spawning_orientation(scene->spawn_orientation);
// 	player.fov = PLAYER_FOV;
// 	player.delta.x = cos(degree_to_radian(player.angle));
// 	player.delta.y = -sin(degree_to_radian(player.angle));
// 	player.cam_plane.x = -player.delta.y * player.fov;
// 	player.cam_plane.y = player.delta.x * player.fov;
// 	player.speed = PLAYER_SPEED;
// 	player.turn_speed = PLAYER_TURN_SPEED;
// 	// 
// 	player.size = PLAYER_SIZE;
// 	player.color = 0xFF00FFFF;
// 	// 
// 	// player.respawn = &player; //need to fix this to create a full copy of player instead..
// 	return (player);
// }

// static t_fpoint	get_velocity(t_cub *cub)
// {
// 	t_fpoint	velocity;

// 	velocity.x = cub->player.delta.x * cub->player.speed;
// 	velocity.y = cub->player.delta.y * cub->player.speed;
// 	return (velocity);
// }

// static float	get_move_value(t_cub *cub, int x, int y, float rtn_value)
// {
// 	int	tile;

// 	tile = check_hit(x, y);
// 	if (tile == 3 && cub->elevator.door == CLOSE
// 		&& !((int) cub->player.position.x == cub->elevator.position.x
// 		&& (int) cub->player.position.y == cub->elevator.position.y))
// 		return (0);
// 	if (tile == 0 && cub->elevator.door == CLOSE
// 		&& (int) cub->player.position.x == cub->elevator.position.x
// 		&& (int) cub->player.position.y == cub->elevator.position.y)
// 		return (0);
// 	if (tile == 1)
// 		return (0);
// 	return (rtn_value);
// }

// void	update_player_position(t_cub *cub)
// {
// 	t_fpoint	speed;
// 	t_fpoint	*pos;

// 	pos = &cub->player.position;
// 	speed = get_velocity(cub);
// 	if (cub->keys.up || cub->keys.w)
// 	{
// 		pos->x += get_move_value(cub, pos->x + speed.x, pos->y, speed.x);
// 		pos->y += get_move_value(cub, pos->x, pos->y + speed.y, speed.y);
// 	}
// 	if (cub->keys.a)
// 	{
// 		pos->x += get_move_value(cub, pos->x + speed.y, pos->y, speed.y);
// 		pos->y -= get_move_value(cub, pos->x, pos->y - speed.x, speed.x);
// 	}
// 	if (cub->keys.down || cub->keys.s)
// 	{
// 		pos->x -= get_move_value(cub, pos->x - speed.x, pos->y, speed.x);
// 		pos->y -= get_move_value(cub, pos->x, pos->y - speed.y, speed.y);
// 	}
// 	if (cub->keys.d)
// 	{
// 		pos->x -= get_move_value(cub, pos->x - speed.y, pos->y, speed.y);
// 		pos->y += get_move_value(cub, pos->x, pos->y + speed.x, speed.x);
// 	}
// }

// static void	apply_rotation_matrix(t_fpoint *src, float turn_speed)
// {
// 	t_fpoint	tmp;

// 	tmp.x = src->x;
// 	tmp.y = src->y;
// 	src->x = tmp.x * cos(turn_speed) - tmp.y * sin(turn_speed);
// 	src->y = tmp.x * sin(turn_speed) + tmp.y * cos(turn_speed);
// }

// void	update_player_direction(t_cub *cub)
// {
// 	t_player	*player;

// 	player = &cub->player;
// 	if (cub->keys.right && !cub->keys.leftcontrol)
// 	{
// 		apply_rotation_matrix(&player->delta, player->turn_speed);
// 		apply_rotation_matrix(&player->cam_plane, player->turn_speed);
// 	}
// 	if (cub->keys.left && !cub->keys.leftcontrol)
// 	{
// 		apply_rotation_matrix(&player->delta, -player->turn_speed);
// 		apply_rotation_matrix(&player->cam_plane, -player->turn_speed);
// 	}
// 	if (cub->mouse.right)
// 	{
// 		apply_rotation_matrix(&player->delta, cub->mouse.rotate_x);
// 		apply_rotation_matrix(&player->cam_plane, cub->mouse.rotate_x);
// 		cub->mouse.right = OFF;
// 	}
// 	if (cub->mouse.left)
// 	{
// 		apply_rotation_matrix(&player->delta, -cub->mouse.rotate_x);
// 		apply_rotation_matrix(&player->cam_plane, -cub->mouse.rotate_x);
// 		cub->mouse.left = OFF;
// 	}
// }

// static void	update_player_stats(t_player *player, t_keys *keys)
// {
// 	player->speedup = keys->leftshift;

// 	if (player->speedup)
// 		player->speed = PLAYER_SPEED * 2;
// 	else
// 		player->speed = PLAYER_SPEED;
// }

// void	update_player(t_cub *cub)
// {
// 	t_player	*player;

// 	player = &cub->player;
// 	// if (cub->keys.backspace)
// 	// 	*player = *player->respawn; //needs a fixing
// 	// 
// 	update_player_stats(player, &cub->keys); //test, might use this for inventory ?
// 	// 
// 	update_player_position(cub);
// 	update_player_direction(cub);
// }
