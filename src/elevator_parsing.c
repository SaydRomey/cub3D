/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevator_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:53:02 by olivierroy        #+#    #+#             */
/*   Updated: 2024/03/29 16:25:17 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static t_point	get_orientation_vector(int orientation)
// {
// 	if (orientation == NO)
// 		return ((t_point){0, -1});
// 	if (orientation == SO)
// 		return ((t_point){0, 1});
// 	if (orientation == EA)
// 		return ((t_point){1, 0});
// 	if (orientation == WE)
// 		return ((t_point){-1, 0});
// 	return ((t_point){0, 0});
// }

static int	check_only_one_side(t_map *map, t_elevator *elevator, int orientation)
{
	if (elevator->orientation == -1)
		return (orientation);
	else
	{
		// Should we change the char here
		// or simply unable the ability to open the door ?
		map->map_array[elevator->position.y][elevator->position.x] = 1;
		return (-2);
	}
}

static void	get_elevator_orientation(t_map *map, t_elevator *elevator)
{
	t_point	pos;

	pos = elevator->position;
	elevator->orientation = -1;
	if (map->map_array[pos.y + 1][pos.x] == 0)
		elevator->orientation = NO;
	if (map->map_array[pos.y - 1][pos.x] == 0)
		elevator->orientation = check_only_one_side(map, elevator, SO);
	if (elevator->orientation != -2 && map->map_array[pos.y][pos.x - 1] == 0)
		elevator->orientation = check_only_one_side(map, elevator, EA);
	if (elevator->orientation != -2 && map->map_array[pos.y][pos.x + 1] == 0)
		elevator->orientation = check_only_one_side(map, elevator, WE);
	if (elevator->orientation == -2)
		elevator->valid = false;
	// elevator->orientation_vector = get_orientation_vector(elevator->orientation);
}

static void	get_elevator_position(t_map *map, t_elevator *elevator)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map_array[y][x] == ELEVATOR)
			{
				elevator->position = (t_point){x, y};
				return ;
			}
			x++;
		}
		y++;
	}
	elevator->valid = false;
}

void	parse_elevator(t_map *map, t_elevator *elevator)
{
	// t_elevator	elevator;

	ft_memset(elevator, 0, sizeof (t_elevator));
	elevator->valid = true;
	get_elevator_position(map, elevator);
	if (elevator->valid)
		get_elevator_orientation(map, elevator);
	if (!elevator->valid)
		printf ("Elevator not valid\n");
	// return (elevator);
}
