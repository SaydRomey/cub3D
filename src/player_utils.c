/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:03:07 by oroy              #+#    #+#             */
/*   Updated: 2024/05/01 19:34:59 by cdumais          ###   ########.fr       */
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

/* ************************************************************************** */

static t_triangle	init_player_icon(t_player *player, t_fpoint offset)
{
	t_triangle	t;

	t.half_base = player->size * tan(degree_to_radian(PLAYER_ICON_ANGLE));
	t.height = player->size * (sqrt(3) / 2);
	t.centroid.x = offset.x - player->delta.x * (t.height / 3);
	t.centroid.y = offset.y - player->delta.y * (t.height / 3);
	t.front.x = t.centroid.x + player->delta.x * player->size;
	t.front.y = t.centroid.y + player->delta.y * player->size;
	t.left.x = t.centroid.x - player->delta.y * t.half_base;
	t.left.y = t.centroid.y + player->delta.x * t.half_base;
	t.right.x = t.centroid.x + player->delta.y * t.half_base;
	t.right.y = t.centroid.y - player->delta.x * t.half_base;
	t.base_center.x = (t.left.x + t.right.x) / 2;
	t.base_center.y = (t.left.y + t.right.y) / 2;
	return (t);
}

void	draw_player(t_minimap *mini, t_player *player)
{
	t_triangle	t;
	t_fpoint	offset;
	
	offset.x = player->position.x * mini->tile_size + mini->offset.x;
	offset.y = player->position.y * mini->tile_size + mini->offset.y;
	t = init_player_icon(player, offset);
	if (!mini->highlight_player_pos)
	{
		draw_line(mini->img, t.base_center, t.front, HEX_BLACK);
		draw_triangle_hollow(mini->img, &t, 8, player->color);
	}
}
