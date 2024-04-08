// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   elevator_events.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/25 17:05:48 by oroy              #+#    #+#             */
// /*   Updated: 2024/04/08 11:42:22 by cdumais          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3d.h"

// static void	check_near_elevator(t_fpoint pos, t_elevator *e)
// {
// 	if (e->map_change == 0 && (check_hit(pos.x, pos.y) == ELEVATOR
// 		|| check_hit(pos.x + DOOR_DISTANCE, pos.y) == ELEVATOR
// 		|| check_hit(pos.x + DOOR_DISTANCE, pos.y - DOOR_DISTANCE) == ELEVATOR
// 		|| check_hit(pos.x, pos.y - DOOR_DISTANCE) == ELEVATOR
// 		|| check_hit(pos.x - DOOR_DISTANCE, pos.y - DOOR_DISTANCE) == ELEVATOR
// 		|| check_hit(pos.x - DOOR_DISTANCE, pos.y) == ELEVATOR
// 		|| check_hit(pos.x - DOOR_DISTANCE, pos.y + DOOR_DISTANCE) == ELEVATOR
// 		|| check_hit(pos.x, pos.y + DOOR_DISTANCE) == ELEVATOR
// 		|| check_hit(pos.x + DOOR_DISTANCE, pos.y + DOOR_DISTANCE) == ELEVATOR))
// 		e->door = OPEN;
// 	else
// 		e->door = CLOSE;
// }

// static void	toggle_elevator_buttons(t_fpoint pos, t_elevator *e)
// {
// 	if (check_hit(pos.x, pos.y) == ELEVATOR)
// 		e->buttons->enabled = true;
// 	else
// 		e->buttons->enabled = false;
// }

// static void	update_door_animation(t_elevator *e)
// {
// 	if (e->door == OPEN)
// 	{
// 		if (e->door_animation.current_frame < e->door_animation.last_frame)
// 			update_animation(&e->door_animation, GO_RIGHT);
// 	}
// 	else
// 	{
// 		if (e->door_animation.current_frame != 0)
// 			update_animation(&e->door_animation, GO_LEFT);
// 		else if (e->map_change == 1)
// 			change_map(call_cub());
// 	}
// }

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

// void	elevator_events(t_cub *cub)
// {
// 	check_near_elevator(cub->player.position, &cub->elevator);
// 	toggle_elevator_buttons(cub->player.position, &cub->elevator);
// 	update_door_animation(&cub->elevator);
// }
