/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevator_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:05:48 by oroy              #+#    #+#             */
/*   Updated: 2024/04/17 01:22:57 by olivierroy       ###   ########.fr       */
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
			change_level(call_cub()->chosen_level);
			update_elevator_struct();
			// e->map_change = 0;
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
	{
		cub->elevator.map_change = 1;
		cub->chosen_level = lvl_index;
	}
}

void	elevator_events(t_cub *cub)
{
	check_near_elevator(cub->player.position, &cub->elevator);

	toggle_elevator_buttons(cub->player.position, &cub->elevator);
	if (cub->elevator.buttons_on)
		check_button_hover(cub->elevator.buttons);

	update_door_animation(&cub->elevator);
}

// void	check_for_map_change(t_cub *cub, int y)
// {
// 	int	width;
// 	int	i;

// 	i = 0;
// 	width = cub->elevator.buttons->width;
// 	while (i < cub->scene_total)
// 	{
// 		if ((y >= HEIGHT - (width + i * width) && y < HEIGHT - i * width)
// 			&& cub->elevator.id != i)
// 		{
// 			draw_buttons(&cub->elevator, i);
// 			cub->elevator.map_change = 1;
// 			cub->elevator.id = i;
// 			break ;
// 		}
// 		i++;
// 	}
// }