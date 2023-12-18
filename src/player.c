/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:54:44 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/18 15:14:58 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	init_player(t_point start)
{
	t_player	player;
	
	player.position.x = start.x;
	player.position.y = start.y;
	player.angle = spawning_orientation('S');
	player.delta.x = cos(degree_to_radian(player.angle));
	player.delta.y = -sin(degree_to_radian(player.angle));
	player.size = PLAYER_SIZE;
	player.color = HEX_PURPLE;
	player.speed = PLAYER_SPEED;
	player.turn_speed = PLAYER_TURN_SPEED;
	return (player);
}

void	draw_player(t_img *img, t_player *player)
{
	t_point	line_size;
	int		ray_length = 42; //tmp
	int		ray_color = HEX_RED; //tmp

	line_size.x = player->position.x + player->delta.x * ray_length;
	line_size.y = player->position.y + player->delta.y * ray_length;
	draw_line(img, player->position, line_size, ray_color);
	draw_circle(img, player->position, player->size, player->color);
}

void	update_player_position(t_cub *cub)
{
	t_player	*player;

	player = &cub->player;
	if (cub->keys.up || cub->keys.w) //move forward
	{
		player->position.x += player->delta.x * player->speed;
		player->position.y += player->delta.y * player->speed;
	}
	if (cub->keys.a) //move left
	{
		player->position.x += player->delta.y * player->speed;
		player->position.y -= player->delta.x * player->speed;
	}
	if (cub->keys.down || cub->keys.s) //move backward
	{
		player->position.x -= player->delta.x * player->speed;
		player->position.y -= player->delta.y * player->speed;
	}
	if (cub->keys.d) //move right
	{
		player->position.x -= player->delta.y * player->speed;
		player->position.y += player->delta.x * player->speed;
	}
}

void	update_player_direction(t_cub *cub)
{
	t_player	*player;

	player = &cub->player;
	if (cub->keys.left) //turn left
	{
		player->angle += player->turn_speed;
		player->angle = fix_angle(player->angle);
		player->delta.x = cos(degree_to_radian(player->angle));
		player->delta.y = -sin(degree_to_radian(player->angle));
	}
	if (cub->keys.right) //turn right
	{
		player->angle -= player->turn_speed;
		player->angle = fix_angle(player->angle);
		player->delta.x = cos(degree_to_radian(player->angle));
		player->delta.y = -sin(degree_to_radian(player->angle));
	}
}
