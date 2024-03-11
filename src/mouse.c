/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:30:16 by oroy              #+#    #+#             */
/*   Updated: 2024/03/11 17:55:24 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_cub	*cub;
	int		divider;
	int		rotate_x;

	(void) ypos;
	cub = param;
	divider = WIDTH / 2;
	rotate_x = xpos - divider;
	if (rotate_x < 0)
	{
		cub->mouse.left = ON;
		cub->mouse.rotate_x = ft_fabs(rotate_x / (float) divider);
	}
	else if (rotate_x > 0)
	{
		cub->mouse.right = ON;
		cub->mouse.rotate_x = ft_fabs(rotate_x / (float) divider);
	}
	mlx_set_mouse_pos(cub->mlx, divider, HEIGHT / 2);
}

void	set_mouse(t_cub *cub)
{
	mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(cub->mlx, WIDTH / 2, HEIGHT / 2);
	mlx_cursor_hook(cub->mlx, &cursor_hook, cub);
}
