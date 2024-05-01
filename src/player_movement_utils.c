/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:17:57 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/01 18:55:41 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_fpoint	get_velocity(t_player *player)
{
	t_fpoint	velocity;

	velocity.x = player->delta.x * player->speed;
	velocity.y = player->delta.y * player->speed;
	return (velocity);
}

float	get_move_value(int x, int y, float rtn_value)
{
	t_cub	*cub;
	int		tile;

	cub = call_cub();
	tile = check_hit(x, y);
	if (tile == 3 && cub->elevator.door == CLOSE \
	&& !((int) cub->player.position.x == cub->elevator.position.x \
	&& (int) cub->player.position.y == cub->elevator.position.y))
		return (0);
	if (tile == 0 && cub->elevator.door == CLOSE
		&& (int) cub->player.position.x == cub->elevator.position.x
		&& (int) cub->player.position.y == cub->elevator.position.y)
		return (0);
	if (tile == 1)
		return (0);
	return (rtn_value);
}

void	apply_rotation_matrix(t_fpoint *src, float turn_speed)
{
	t_fpoint	tmp;

	tmp.x = src->x;
	tmp.y = src->y;
	src->x = tmp.x * cos(turn_speed) - tmp.y * sin(turn_speed);
	src->y = tmp.x * sin(turn_speed) + tmp.y * cos(turn_speed);
}

/* ************************************************************************** */

t_fpoint	rotate_vector_position(t_fpoint tmp, int rotation)
{
	t_fpoint	new;

	if (rotation == -90 || rotation == 270)
	{
		new.x = 1 - tmp.y;
		new.y = tmp.x;
	}
	else if (rotation == 90 || rotation == -270)
	{
		new.x = tmp.y;
		new.y = 1 - tmp.x;
	}
	else
	{
		new.x = 1 - tmp.x;
		new.y = 1 - tmp.y;
	}
	return (new);
}

t_fpoint	rotate_vector_delta(t_fpoint tmp, int rotation)
{
	t_fpoint	new;

	if (rotation == -90 || rotation == 270)
	{
		new.x = tmp.y;
		new.y = -tmp.x;
	}
	else if (rotation == 90 || rotation == -270)
	{
		new.x = -tmp.y;
		new.y = tmp.x;
	}
	else
	{
		new.x = -tmp.x;
		new.y = -tmp.y;
	}
	return (new);
}
