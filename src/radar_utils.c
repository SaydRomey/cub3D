/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:32:23 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/24 19:36:16 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
