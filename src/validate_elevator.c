/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elevator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:59:43 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/24 17:56:00 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	  1
	1 3 1
	  0  
*/
static bool	check_north(int **map, int y, int x)
{
	int	wall_count;
	int	valid;

	wall_count = 0;
	valid = map[y + 1][x] == 0;
	wall_count += map[y][x + 1] == 1;
	wall_count += map[y][x - 1] == 1;
	wall_count += map[y - 1][x] == 1;
	return (valid && wall_count == 3);
}

/*
	  0
	1 3 1
	  1  
*/
static bool	check_south(int **map, int y, int x)
{
	int	wall_count;
	int	valid;

	wall_count = 0;
	valid = map[y - 1][x] == 0;
	wall_count += map[y][x + 1] == 1;
	wall_count += map[y][x - 1] == 1;
	wall_count += map[y + 1][x] == 1;
	return (valid && wall_count == 3);
}

/*
	  1
	0 3 1
	  1  
*/
static bool	check_east(int **map, int y, int x)
{
	int	wall_count;
	int	valid;

	wall_count = 0;
	valid = map[y][x - 1] == 0;
	wall_count += map[y + 1][x] == 1;
	wall_count += map[y - 1][x] == 1;
	wall_count += map[y][x + 1] == 1;
	return (valid && wall_count == 3);
}

/*
	  1
	1 3 0
	  1  
*/
static bool	check_west(int **map, int y, int x)
{
	int	wall_count;
	int	valid;

	wall_count = 0;
	valid = map[y][x + 1] == 0;
	wall_count += map[y + 1][x] == 1;
	wall_count += map[y - 1][x] == 1;
	wall_count += map[y][x - 1] == 1;
	return (valid && wall_count == 3);
}

/*
elevator orientation is the direction the player needs to face to enter)

*/
int	get_elevator_orientation(int **map, t_point *position)
{
	int		y;
	int		x;

	y = position->y;
	x = position->x;
	if (map[y][x] != ELEVATOR)
		return (-1);
	if (check_north(map, y, x))
		return (cardinal_to_radian('N'));
	else if (check_south(map, y, x))
		return (cardinal_to_radian('S'));
	else if (check_east(map, y, x))
		return (cardinal_to_radian('E'));
	else if (check_west(map, y, x))
		return (cardinal_to_radian('W'));
	return (-1);
}

/* ************************************************************************** */
/* ************************************************************************** */

void	get_elevator_info(t_level *lvl, t_map *map)
{
	t_point	*pos;

	pos = &lvl->elevator_position;
	lvl->elevator_exists = find_value_in_array(map, ELEVATOR, pos);
	if (lvl->elevator_exists)
		lvl->elevator_orientation = \
	get_elevator_orientation(map->map_array, pos);
}

/* ************************************************************************** */
/* ************************************************************************** */

bool	valid_elevator(int **map, int y, int x) //is this used ?
{
	if (check_north(map, y, x))
		return (true);
	if (check_south(map, y, x))
		return (true);
	if (check_east(map, y, x))
		return (true);
	if (check_west(map, y, x))
		return (true);
	return (false);
}
