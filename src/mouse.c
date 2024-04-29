/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:30:16 by oroy              #+#    #+#             */
/*   Updated: 2024/04/29 13:26:56 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	mouse_click_events(t_cub *cub)
{
	if (get_level(cub->current_level)->elevator_exists)
	{
		if (cub->elevator.buttons[0].button_imgs[1]->instances->enabled)
			elevator_change_map(cub->current_level + 1);
		if (cub->elevator.buttons[1].button_imgs[1]->instances->enabled)
			elevator_change_map(cub->current_level - 1);
	}
}

static void	set_mouse_mode(bool enabled)
{
	mlx_t	*mlx;

	mlx = call_cub()->mlx;
	if (enabled)
	{
		mlx_set_cursor_mode(mlx, MLX_MOUSE_HIDDEN);
		mlx_set_mouse_pos(mlx, WIDTH / 2, HEIGHT / 2);
	}
	else
		mlx_set_cursor_mode(mlx, MLX_MOUSE_NORMAL);
}


/*
to check, cannot void an enum on linux.. ?

*/
static void	mouse_hook(mouse_key_t btn, action_t a, modifier_key_t m, void *param)
{
	t_cub	*cub;

	if (m == 42)
		ft_printf("is this only a problem on linux ?\n");
	cub = (t_cub *)param;
	if (btn == MLX_MOUSE_BUTTON_RIGHT && a == MLX_PRESS)
		toggle(&cub->mouse.enabled);
	if (btn == MLX_MOUSE_BUTTON_LEFT && a == MLX_PRESS)
		mouse_click_events(cub);
	set_mouse_mode(cub->mouse.enabled);
}

static void	cursor_hook(double xpos, double ypos, void *param)
{
	t_cub	*cub;
	int		divider;
	int		rotate_x;

	(void) ypos;
	cub = (t_cub *)param;
	divider = WIDTH / 2;
	rotate_x = xpos - divider;
	if (!cub->mouse.enabled)
		return ;
	if (rotate_x < 0)
		cub->mouse.left = ON;
	if (rotate_x > 0)
		cub->mouse.right = ON;
	cub->mouse.rotate_x = ft_fabs(rotate_x / (float)divider);
	set_mouse_mode(cub->mouse.enabled);
}

void	set_mouse(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	cub->mouse.enabled = ON;
	set_mouse_mode(cub->mouse.enabled);
	mlx_cursor_hook(cub->mlx, &cursor_hook, cub);
	mlx_mouse_hook(cub->mlx, &mouse_hook, cub);
}
