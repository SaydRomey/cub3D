/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:09:05 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/16 20:58:30 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_cub *cub)
{
	if (key == ESC)
		cub->keys.esc = 1;
	if (key == W)
		cub->keys.w = 1;
	if (key == A)
		cub->keys.a = 1;
	if (key == S)
		cub->keys.s = 1;
	if (key == D)
		cub->keys.d = 1;
	if (key == LEFT)
		cub->keys.left = 1;
	if (key == RIGHT)
		cub->keys.right = 1;
	return (0);
}

int	key_release(int key, t_cub *cub)
{
	if (key == W)
		cub->keys.w = 0;
	if (key == A)
		cub->keys.a = 0;
	if (key == S)
		cub->keys.s = 0;
	if (key == D)
		cub->keys.d = 0;
	if (key == LEFT)
		cub->keys.left = 0;
	if (key == RIGHT)
		cub->keys.right = 0;
	return (0);
}

void	check_options(t_cub *cub)
{
	if (cub->keys.esc)
		terminate_mlx(cub);
}

/* for mlx_loop_hook */
int	update_game(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	update_player_position(cub);
	update_player_direction(cub);
	check_options(cub);
	render(cub);
	return (0);
}

// int	key_print(int key, t_cub *cub)
// {
// 	(void)cub;

// 	ft_printf("key: %d\n", key);
// 	return (0);
// }
