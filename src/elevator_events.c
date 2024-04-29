/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevator_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:05:48 by oroy              #+#    #+#             */
/*   Updated: 2024/04/29 14:03:54 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_near_elevator(t_fpoint pos, t_elevator *e)
{
	if (e->map_change == 0 && (check_hit(pos.x, pos.y) == ELEVATOR
			|| check_hit(pos.x + 1, pos.y) == ELEVATOR
			|| check_hit(pos.x + 1, pos.y - 1) == ELEVATOR
			|| check_hit(pos.x, pos.y - 1) == ELEVATOR
			|| check_hit(pos.x - 1, pos.y - 1) == ELEVATOR
			|| check_hit(pos.x - 1, pos.y) == ELEVATOR
			|| check_hit(pos.x - 1, pos.y + 1) == ELEVATOR
			|| check_hit(pos.x, pos.y + 1) == ELEVATOR
			|| check_hit(pos.x + 1, pos.y + 1) == ELEVATOR))
		e->door = OPEN;
	else
		e->door = CLOSE;
}
static void	toggle_elevator_buttons(t_fpoint pos, t_elevator *e)
{
	if (check_hit(pos.x, pos.y) == ELEVATOR)
	{
		if (!e->buttons_on)
		{
			e->buttons_on = true;
			e->buttons[0].button_imgs[0]->instances->enabled = true;
			e->buttons[1].button_imgs[0]->instances->enabled = true;
		}
	}
	else
	{
		if (e->buttons_on)
		{
			e->buttons_on = false;
			e->buttons[0].button_imgs[0]->instances->enabled = false;
			e->buttons[0].button_imgs[1]->instances->enabled = false;
			e->buttons[1].button_imgs[0]->instances->enabled = false;
			e->buttons[1].button_imgs[1]->instances->enabled = false;
		}
	}
}

static void	update_door_animation(t_elevator *e)
{
	if (e->door == OPEN)
	{
		if (e->door_animation.current_frame < e->door_animation.last_frame)
			update_animation(&e->door_animation, GO_RIGHT);
	}
	else
	{
		if (e->door_animation.current_frame != 0)
			update_animation(&e->door_animation, GO_LEFT);
		else if (e->map_change == 1)
		{
			// elevator_waiting();
			// elevator_waiting();
			change_level(call_cub()->chosen_level);
		}
	}
}

void	elevator_change_map(int lvl_index)
{
	t_cub	*cub;

	cub = call_cub();
	if (get_level(lvl_index)
		&& !(get_level(cub->current_level)->is_segworld
			&& lvl_index > cub->current_level))
			&& lvl_index > cub->current_level))
	{
		cub->elevator.map_change = 1;
		cub->chosen_level = lvl_index;
	}
}

void	elevator_events(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	check_near_elevator(cub->player.position, &cub->elevator);
	toggle_elevator_buttons(cub->player.position, &cub->elevator);
	if (cub->elevator.buttons_on)
		check_button_hover(cub->elevator.buttons);
	update_door_animation(&cub->elevator);
}

// static	void check_near_elevator(t_fpoint pos, t_elevator *e)
// {
// 	int	dx;
// 	int	dy;

// 	if (e->map_change == 0)
// 	{
// 		dy = -1;
// 		while (dy <= 1)
// 		{
// 			dx = -1;
// 			while (dx <= 1)
// 			{
// 				if (check_hit(pos.x + dx, pos.y + dy) == ELEVATOR)
// 				{
// 					e->door = OPEN;
// 					return ;
// 				}
// 				dx++;
// 			}
// 			dy++;
// 		}
// 	}
// 	e->door = CLOSE;
// }
