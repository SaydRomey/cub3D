/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:09:30 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/18 14:59:56 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
sets the mouse cursor location in t_cub
*/
int follow_mouse(int mouse_x, int mouse_y, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	cub->cursor.x = mouse_x;
	cub->cursor.y = mouse_y;
	// if (mouse_x > 0 && mouse_y > 0 && mouse_x < WIDTH && mouse_y < HEIGHT) //tmp
	// {
	// 	ft_printf("mouse x = %d\n", mouse_x);
	// 	ft_printf("mouse y = %d\n", mouse_y);
	// }
	return (0);
}

/*
in render, draws a circle at cursor location
also draws a line from the player to the cursor
*/
void	draw_cursor(t_img *img, t_cub *cub)
{
	t_player	*player;
	t_point		cursor;

	player = &cub->player;
	cursor = cub->cursor;
	if (cursor.x > 0 && cursor.y > 0 && cursor.x < WIDTH && cursor.y < HEIGHT)
	{
		draw_circle(img, cursor, 5, HEX_BLUE);
	}
	if (cub->line_switch)
		draw_line(img, player->position, cursor, HEX_GREEN);
}

/*
triggered with mouse click or scroll
*/
int read_mouse(int button, int mouse_x, int mouse_y, void *param)
{
	t_cub 		*cub;

	cub = (t_cub *)param;
	if (mouse_x < 0 || mouse_y < 0 || mouse_x > WIDTH || mouse_y > HEIGHT)
		return (FAILURE);
	ft_printf("mouse button: %d\n", button);
	if (button == L_CLICK)
		toggle(&cub->line_switch);
	// 
	return (0);
}
