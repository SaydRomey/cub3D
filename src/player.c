/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:14:10 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/06 16:21:21 by cdumais          ###   ########.fr       */
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

t_player	init_player(t_fpoint start, char direction)
{
	t_player	player;
	
	player.position.x = start.x;
	player.position.y = start.y;
	player.angle = spawning_orientation(direction);
	player.fov = PLAYER_FOV;
	player.delta.x = cos(degree_to_radian(player.angle));
	player.delta.y = -sin(degree_to_radian(player.angle));
	player.cam_plane.x = -player.delta.y * player.fov;
	player.cam_plane.y = player.delta.x * player.fov;
	// 
	player.size = PLAYER_SIZE;
	player.color = 0xFF00FFFF;
	player.speed = PLAYER_SPEED;
	player.turn_speed = PLAYER_TURN_SPEED;
	// 
	player.respawn = &player;
	return (player);
}

static float	get_move_value(int x, int y, float rtn_value, int **map_array)
{
	if (!check_hit2(x, y, map_array))
		return (rtn_value);
	return (0);
}

static t_fpoint	get_velocity(t_cub *cub)
{
	t_fpoint	velocity;

	velocity.x = cub->player.delta.x * cub->player.speed;
	velocity.y = cub->player.delta.y * cub->player.speed;
	return (velocity);
}

void	update_player_position(t_cub *cub)
{
	t_fpoint	velocity;
	t_fpoint	*pos;
	int			**map_array = cub->map.map_array;

	pos = &cub->player.position;
	velocity = get_velocity(cub);
	if (cub->keys.up || cub->keys.w)
	{
		pos->x += get_move_value(pos->x + velocity.x, pos->y, velocity.x, map_array);
		pos->y += get_move_value(pos->x, pos->y + velocity.y, velocity.y, map_array);
	}
	if (cub->keys.a)
	{
		pos->x += get_move_value(pos->x + velocity.y, pos->y, velocity.y, map_array);
		pos->y -= get_move_value(pos->x, pos->y - velocity.x, velocity.x, map_array);
	}
	if (cub->keys.down || cub->keys.s)
	{
		pos->x -= get_move_value(pos->x - velocity.x, pos->y, velocity.x, map_array);
		pos->y -= get_move_value(pos->x, pos->y - velocity.y, velocity.y, map_array);
	}
	if (cub->keys.d)
	{
		pos->x -= get_move_value(pos->x - velocity.y, pos->y, velocity.y, map_array);
		pos->y += get_move_value(pos->x, pos->y + velocity.x, velocity.x, map_array);
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

void	update_player(t_cub *cub)
{
	t_player	*player;

	player = &cub->player;
	if (cub->keys.backspace)
		*player = *player->respawn;
	// 
	update_player_position(cub);
	update_player_direction(cub);
	// 
	// if (cub->keys.p)
	// 	draw_player2(cub->minimap_img, &cub->player);
	// else
	// 	draw_player(cub->minimap_img, &cub->player);
}

// void	draw_player(mlx_image_t *img, t_player *player)
// {
// 	t_fpoint	line_size;
// 	int		ray_length = 42; //tmp
// 	int		ray_color = 0x00FF00FF; //tmp

// 	line_size.x = player->position.x + player->delta.x * ray_length;
// 	line_size.y = player->position.y + player->delta.y * ray_length;
// 	draw_line(img, player->position, line_size, ray_color);
// 	draw_circle(img, player->position, player->size, player->color);
// }

// void	draw_player2(mlx_image_t *img, t_player *player)
// {
// 	t_fpoint	front;
// 	t_fpoint	left;
// 	t_fpoint	right;
// 	// t_fpoint	base_center;
// 	float	half_base;
	
// 	half_base = player->size * tan(degree_to_radian(30)); // 30 degrees for equilateral triangle

// 	// Front vertex of the triangle
// 	front.x = player->position.x + player->delta.x * player->size;
// 	front.y = player->position.y + player->delta.y * player->size;

// 	// Left and right vertices
// 	left.x = player->position.x - player->delta.y * half_base;
// 	left.y = player->position.y + player->delta.x * half_base;
// 	right.x = player->position.x + player->delta.y * half_base;
// 	right.y = player->position.y - player->delta.x * half_base;

// 	// Calculating the midpoint of the base
// 	// base_center.x = (left.x + right.x) / 2;
// 	// base_center.y = (left.y + right.y) / 2;

// 	draw_triangle(img, front, left, right, player->color);
// 	// draw_line(img, base_center, front, player->color);
// 	// draw_circle_hollow(img, player->position, player->size, 2, HEX_ORANGE);
// }
