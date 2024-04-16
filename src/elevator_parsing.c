/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevator_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:53:02 by olivierroy        #+#    #+#             */
/*   Updated: 2024/04/15 15:19:47 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	get_elevator_orientationnn(t_map *map, t_elevator *elevator)
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
	elevator->valid = true;
    
	get_elevator_position(map, elevator);
	if (elevator->valid)
		get_elevator_orientationnn(map, elevator);
    
	if (!elevator->valid)
    {
        set_error("Invalid elevator");
        error();
    }
}
