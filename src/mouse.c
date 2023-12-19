/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:09:30 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/19 15:06:01 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int moving_left(t_cub *cub)
{
	if (!is_in_window(cub->cursor))
		return (FALSE);
	return (cub->prev_cursor.x > cub->cursor.x);
}

int moving_right(t_cub *cub)
{
	if (!is_in_window(cub->cursor))
		return (FALSE);
	return (cub->prev_cursor.x < cub->cursor.x);
}

int moving_up(t_cub *cub)
{
	if (!is_in_window(cub->cursor))
		return (FALSE);
	return (cub->prev_cursor.y > cub->cursor.y);
}

int moving_down(t_cub *cub)
{
	if (!is_in_window(cub->cursor))
		return (FALSE);
	return (cub->prev_cursor.y < cub->cursor.y);
}

/*
sets the mouse cursor location in t_cub
**triggered on mouse movement*
*/
int follow_mouse(int mouse_x, int mouse_y, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	
	// update previous cursor position
	// cub->prev_cursor = cub->cursor; //more efficient if in the 'render()' loop

	// update current cursor position
	cub->cursor.x = mouse_x;
	cub->cursor.y = mouse_y;
	// if (mouse_x > 0 && mouse_y > 0 && mouse_x < WIDTH && mouse_y < HEIGHT)
		// ft_printf("mouse [x = %d, y = %d]\n", mouse_x, mouse_y); //tmp
	// 
	update_player_direction(cub);
	// if (cub->info_switch) //tmp
	// {
	// 	if (moving_left(cub))
	// 		ft_printf("going left\n");
	// 	if (moving_right(cub))
	// 		ft_printf("going right\n");
	// 	if (moving_up(cub))
	// 		ft_printf("going up\n");
	// 	if (moving_down(cub))
	// 		ft_printf("going down\n");
	// }
	if (moving_up(cub))
	{
		if (cub->horizon.y >= 100)
			cub->horizon.y -= 1;
	}
	if (moving_down(cub))
	{
		if (cub->horizon.y <= HEIGHT - 100)
			cub->horizon.y += 1;
	}
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
		draw_circle_hollow(img, cursor, 20, 4, HEX_BLACK);
		if (cub->line_switch)
		{
			if (is_in_the_zone(cursor, (t_point){64, 64}, (t_point){64 * 7, 64 * 7}))
				draw_line(img, player->position, cursor, HEX_GREEN);
			else
				draw_line(img, player->position, cursor, HEX_RED);
		}
	}
}

/*
to prevent accidents..
*/
static float	speed_limit(float speed, float limit)
{
	if (speed >= limit)
		return (limit);
	if (speed <= 0)
		return (0);
	return (speed);
}

/*
**triggered with mouse click or scroll*
*/
int read_mouse(int button, int mouse_x, int mouse_y, void *param)
{
	t_cub 		*cub;

	cub = (t_cub *)param;
	if (mouse_x < 0 || mouse_y < 0 || mouse_x > WIDTH || mouse_y > HEIGHT)
		return (FAILURE);
	// ft_printf("mouse button: %d\n", button); //tmp
	if (button == L_CLICK)
		toggle(&cub->line_switch);
	if (button == R_CLICK)
		toggle(&cub->info_switch);
	if (button == SCROLL_UP)
		cub->player.speed += 0.5;
	if (button == SCROLL_DOWN)
		cub->player.speed -= 0.5;
	cub->player.speed = speed_limit(cub->player.speed, SPEED_LIMIT);
	// printf("speed-> %f\n", cub->player.speed); //tmp
	return (0);
}
