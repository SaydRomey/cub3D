/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:30:16 by oroy              #+#    #+#             */
/*   Updated: 2024/04/10 19:44:51 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	mouse_events(t_cub *cub)
// {
// 	int	x;
// 	int	y;

// 	mlx_get_mouse_pos(cub->mlx, &x, &y);
// 	if (cub->elevator.buttons->enabled == true
// 		&& x >= (int)(WIDTH - cub->elevator.buttons->width) && x < WIDTH
// 		&& y >= (int)(HEIGHT - cub->elevator.buttons->height) && y < HEIGHT)
// 		check_for_map_change(cub, y);
// }

static void	set_mouse_mode(bool enabled) // should we use (if SPACEBAR, set mouse mode off (normal), when released enable ?)
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

static void	mouse_hook(mouse_key_t btn, action_t a, modifier_key_t m, void *param)
{
	t_cub	*cub;

	// void (m);//cannot void an enum ?
	if (m == 42)
		ft_printf("is this only a problem on linux ?\n");
	cub = (t_cub *)param;
	if (btn == MLX_MOUSE_BUTTON_RIGHT && a == MLX_PRESS)
		toggle(&cub->mouse.enabled);
	// if (btn == MLX_MOUSE_BUTTON_LEFT && a == MLX_PRESS)
	// 	mouse_events(cub);
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

void	set_mouse(t_cub *cub)
{
	cub->mouse.enabled = ON; //if BONUS?
	set_mouse_mode(cub->mouse.enabled);
	mlx_cursor_hook(cub->mlx, &cursor_hook, cub);
	mlx_mouse_hook(cub->mlx, &mouse_hook, cub);
	proof("mouse hooked");
}

/*
typedef enum mouse_key
{
	MLX_MOUSE_BUTTON_LEFT	= 0,
	MLX_MOUSE_BUTTON_RIGHT	= 1,
	MLX_MOUSE_BUTTON_MIDDLE	= 2,
}	mouse_key_t;

typedef enum mouse_mode
{
	MLX_MOUSE_NORMAL	= 0x00034001,
	MLX_MOUSE_HIDDEN	= 0x00034002,
	MLX_MOUSE_DISABLED	= 0x00034003,
}	mouse_mode_t;

bool mlx_is_mouse_down(mlx_t* mlx, mouse_key_t key);
void mlx_get_mouse_pos(mlx_t* mlx, int32_t* x, int32_t* y);
void mlx_set_mouse_pos(mlx_t* mlx, int32_t x, int32_t y);
void mlx_set_cursor_mode(mlx_t* mlx, mouse_mode_t mode);

void mlx_mouse_hook(mlx_t* mlx, mlx_mousefunc func, void* param); //called when a mouse does any sort of action, such as pressing a key
void mlx_cursor_hook(mlx_t* mlx, mlx_cursorfunc func, void* param); //called when the mouse position changes
*/
