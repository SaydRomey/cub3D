/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:23:36 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/24 20:06:55 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_toggle_keys(int key, t_keys *keys, bool state)
{
	if (state == ON)
	{
		if (key == M)
			toggle(&keys->m);
		if (key == P)
			toggle(&keys->p);
		if (key == K_1)
			toggle(&keys->one);
		if (key == K_2)
			toggle(&keys->two);
		if (key == K_3)
			toggle(&keys->three);
	}
}

static void	set_extra_keys(int key, t_keys *keys, bool state)
{
	if (key == SPACEBAR)
		keys->spacebar = state;
	if (key == BACKSPACE)
		keys->backspace = state;
	if (key == LEFTSHIFT)
		keys->leftshift = state;
	if (key == LEFTCONTROL)
		keys->leftcontrol = state;
}

static void	set_keys(int key, t_keys *keys, bool state)
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
	set_extra_keys(key, keys, state);
	set_toggle_keys(key, keys, state);
}

void	keyhooks(mlx_key_data_t data, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (data.key == ESC && data.action == PRESS)
	{
		mlx_close_window(cub->mlx);
		cleanup(cub);
		exit(SUCCESS);
	}
	set_keys(data.key, &cub->keys, data.action);
}

/* **in this function we can associate keys to booleans in various structs *!!

*/
void	update_controls(void *param)
{
	t_cub	*cub;
	t_keys	*keys;
	t_level	*lvl;

	cub = (t_cub *)param;
	keys = &cub->keys;
	lvl = get_level(cub->current_level);
	if (lvl)
	{
		lvl->mini.img->instances->enabled = (keys->leftcontrol);
	}
	cub->radar_img->instances->enabled = keys->m;
	cub->vfx.shadow.enabled = keys->one;
	cub->player.speedup = keys->leftshift;
}
