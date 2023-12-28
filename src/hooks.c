/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:09:05 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/27 21:39:31 by cdumais          ###   ########.fr       */
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
	if (key == UP)
		cub->keys.up = 1;
	if (key == LEFT)
		cub->keys.left = 1;
	if (key == DOWN)
		cub->keys.down = 1;
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
	if (key == UP)
		cub->keys.up = 0;
	if (key == LEFT)
		cub->keys.left = 0;
	if (key == DOWN)
		cub->keys.down = 0;
	if (key == RIGHT)
		cub->keys.right = 0;
	return (0);
}

/*
checks if a key is pressed, to call a function
*/
void	check_options(t_cub *cub)
{
	if (cub->keys.esc)
		terminate_mlx(cub);
	// if (cub->keys.map_key)
		// toggle(cub->map.display); add a toggle option to display minimap
}

/*
for mlx_loop_hook
*/
int	update_game(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	update_player_position(cub); //wasd
	update_player_direction(cub); //left, right and mouse
	check_options(cub); //like terminate, (will add parameters here (display..., etc))
	render(cub);
	return (0);
}
