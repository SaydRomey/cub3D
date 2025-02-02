/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:23:36 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/02 15:44:35 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_toggle_keys(int key, t_keys *keys, bool state)
{
	if (state == ON)
	{
		if (key == MLX_KEY_M)
			toggle(&keys->m);
		if (key == MLX_KEY_P)
			toggle(&keys->p);
		if (key == MLX_KEY_R)
			toggle(&keys->r);
		if (key == MLX_KEY_1)
			toggle(&keys->one);
		if (key == MLX_KEY_2)
			toggle(&keys->two);
		if (key == MLX_KEY_3)
			toggle(&keys->three);
	}
}

static void	set_extra_keys(int key, t_keys *keys, bool state)
{
	if (key == MLX_KEY_SPACE)
		keys->spacebar = state;
	if (key == MLX_KEY_BACKSPACE)
		keys->backspace = state;
	if (key == MLX_KEY_LEFT_SHIFT)
		keys->leftshift = state;
	if (key == MLX_KEY_LEFT_CONTROL)
		keys->leftcontrol = state;
}

static void	set_keys(int key, t_keys *keys, bool state)
{
	if (key == MLX_KEY_W)
		keys->w = state;
	if (key == MLX_KEY_A)
		keys->a = state;
	if (key == MLX_KEY_S)
		keys->s = state;
	if (key == MLX_KEY_D)
		keys->d = state;
	if (key == MLX_KEY_UP)
		keys->up = state;
	if (key == MLX_KEY_LEFT)
		keys->left = state;
	if (key == MLX_KEY_DOWN)
		keys->down = state;
	if (key == MLX_KEY_RIGHT)
		keys->right = state;
	set_extra_keys(key, keys, state);
	set_toggle_keys(key, keys, state);
}

void	keyhooks(mlx_key_data_t data, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (data.key == MLX_KEY_ESCAPE && data.action == MLX_PRESS)
	{
		mlx_close_window(cub->mlx);
		cleanup(cub);
		exit(SUCCESS);
	}
	set_keys(data.key, &cub->keys, data.action);
}

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
		lvl->mini.img->instances->enabled = (keys->m);
		lvl->mini.highlight_player_pos = (keys->m);
	}
	cub->radar_img->instances->enabled = (!keys->m);
	cub->player.speedup = keys->leftshift;
	cub->vfx.textures_enabled = !keys->one;
	cub->vfx.shadow_enabled = keys->two;
}
