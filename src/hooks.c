/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:23:36 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/21 20:19:20 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define PRESS 1
# define RELEASE 0

# define ESC 256
# define W 87
# define A 65
# define S 83
# define D 68
# define UP 265
# define LEFT 263
# define DOWN 264
# define RIGHT 262
# define M 77
# define P 80
# define BACKSPACE 259

static void	set_key(int key, t_keys *keys, bool state)
{
	if (key == W)
		keys->w = state;
	if (key == A)
		keys->a = state;
	if (key == S)
		keys->s = state;
	if (key == D)
		keys->d = state;
	if (key == UP)
		keys->up = state;
	if (key == LEFT)
		keys->left = state;
	if (key == DOWN)
		keys->down = state;
	if (key == RIGHT)
		keys->right = state;
	if (key == BACKSPACE)
		keys->backspace = state;
}

void	keyhooks(mlx_key_data_t data, void *param)
{
	t_cub		*cub;
	t_keys		*keys;

	cub = (t_cub *)param;
	keys = &cub->keys;
	if (data.key == ESC && data.action == PRESS)
	{
		mlx_close_window(cub->mlx);
		cleanup(cub);
		exit(SUCCESS);
	}
	if (data.key == M && data.action == PRESS)
		toggle(&(cub->minimap_img->enabled));
	if (data.key == P && data.action == PRESS)
		toggle(&cub->keys.p);
	// 
	if (data.action == PRESS)
		set_key(data.key, &cub->keys, ON);
	if (data.action == RELEASE)
		set_key(data.key, &cub->keys, OFF);
}

/*
to be called in mlx_loop_hook()
*/
void	update(void *ptr)
{
	t_cub	*cub;

	cub = (t_cub *)ptr;

	// 
	clear_img(cub->img);
	draw_line(cub->img, (t_point){0, 0}, (t_point){WIDTH, HEIGHT}, 0xFF0000FF);

	// reset minimap (also erases the player)
	clear_img(cub->minimap_img);
	draw_minimap(cub->minimap_img, &cub->minimap);

	// update player by checking the keys pressed
	update_player(cub);
	// 
}