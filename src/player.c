/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:14:10 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/22 13:24:31 by cdumais          ###   ########.fr       */
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

t_player	init_player(t_point start, char direction)
{
	t_player	player;
	
	player.position.x = start.x;
	player.position.y = start.y;
	player.angle = spawning_orientation(direction);
	player.delta.x = cos(degree_to_radian(player.angle));
	player.delta.y = -sin(degree_to_radian(player.angle));
	// 
	player.size = PLAYER_SIZE;
	player.color = 0xFF00FFFF;
	player.speed = PLAYER_SPEED;
	player.turn_speed = PLAYER_TURN_SPEED;
	// 
	player.respawn = &player;
	return (player);
}

/*
need to add limitations to stay inside the minimap (maybe wall collisions later?)
*/
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

void	update_player(t_cub *cub)
{
	t_player	*player;

	player = &cub->player;
	if (cub->keys.backspace)
		*player = *player->respawn;
	// 
	update_player_position(cub);
	update_player_direction(cub);
	if (cub->keys.p)
		draw_player2(cub->minimap_img, &cub->player);
	else
		draw_player(cub->minimap_img, &cub->player);
}

void	draw_player(mlx_image_t *img, t_player *player)
{
	t_point	line_size;
	int		ray_length = 42; //tmp
	int		ray_color = 0x00FF00FF; //tmp

	line_size.x = player->position.x + player->delta.x * ray_length;
	line_size.y = player->position.y + player->delta.y * ray_length;
	draw_line(img, player->position, line_size, ray_color);
	draw_circle(img, player->position, player->size, player->color);
}

void	draw_player2(mlx_image_t *img, t_player *player)
{
	t_point	front;
	t_point	left;
	t_point	right;
	// t_point	base_center;
	float	half_base;
	
	half_base = player->size * tan(degree_to_radian(30)); // 30 degrees for equilateral triangle

	// Front vertex of the triangle
	front.x = player->position.x + player->delta.x * player->size;
	front.y = player->position.y + player->delta.y * player->size;

	// Left and right vertices
	left.x = player->position.x - player->delta.y * half_base;
	left.y = player->position.y + player->delta.x * half_base;
	right.x = player->position.x + player->delta.y * half_base;
	right.y = player->position.y - player->delta.x * half_base;

	// Calculating the midpoint of the base
	// base_center.x = (left.x + right.x) / 2;
	// base_center.y = (left.y + right.y) / 2;

	draw_triangle(img, front, left, right, player->color);
	// draw_line(img, base_center, front, player->color);
	// draw_circle_hollow(img, player->position, player->size, 2, HEX_ORANGE);
}
