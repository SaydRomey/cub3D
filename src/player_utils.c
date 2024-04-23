/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:03:07 by oroy              #+#    #+#             */
/*   Updated: 2024/04/22 20:10:51 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

bool	player_is_in_elevator(t_player *player)
{
	t_level	*lvl;

	lvl = get_level(call_cub()->current_level);
	if (lvl)
	{
		if (lvl->elevator_position.x == (int)player->position.x && \
			lvl->elevator_position.y == (int)player->position.y)
			return (true);
	}
	return (false);
}
