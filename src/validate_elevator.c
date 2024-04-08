/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elevator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:59:43 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/08 10:59:29 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static bool	check_north(int **map_array, int y, int x)
// {
// 	return (map_array[y - 1][x] == 1 && 
// 			map_array[y - 1][x - 1] == 1 && 
// 			map_array[y - 1][x + 1] == 1);
// }

// static bool	check_south(int **map_array, int y, int x)
// {
// 	return (map_array[y + 1][x] == 1 && 
// 			map_array[y + 1][x - 1] == 1 && 
// 			map_array[y + 1][x + 1] == 1);
// }

// static bool	check_east(int **map_array, int y, int x)
// {
// 	return (map_array[y][x + 1] == 1 && 
// 			map_array[y - 1][x + 1] == 1 && 
// 			map_array[y + 1][x + 1] == 1);
// }

// static bool	check_west(int **map_array, int y, int x)
// {
// 	return (map_array[y][x - 1] == 1 && 
// 			map_array[y - 1][x - 1] == 1 && 
// 			map_array[y + 1][x - 1] == 1);
// }

// typedef bool	(*t_dir_fptr(int **, int, int));

// static bool	is_valid_direction(t_dir_fptr direction_func, int **map_array, int y, int x)
// {
// 	return (direction_func(map_array, y, x));
// // }

// static bool	is_valid_direction(bool (*direction_func)(int **, int, int), int **map_array, int y, int x)
// {
// 	return (direction_func(map_array, y, x));
// }

// bool	valid_elevator(int **map_array, int y, int x)
// {
// 	int	up;
// 	int	down;
// 	int	left;
// 	int	right;
	
// 	if (map_array[y][x] != 2)
// 		return (false); //would not go here if previously checked
	
// 	up = (map_array[y - 1][x] == 0);
// 	down = (map_array[y + 1][x] == 0);
// 	left = (map_array[y][x - 1] == 0);
// 	right = (map_array[y][x + 1] == 0);
		
// 	if ((up + down + left + right) != 1)
// 		return (false); //more than one '0'
// 	if (up)
// 		return (is_valid_direction(check_north, map_array, y - 1, x));
// 	if (down)
// 		return (is_valid_direction(check_south, map_array, y + 1, x));
// 	if (left)
// 		return (is_valid_direction(check_west, map_array, y, x - 1));
// 	if (right)
// 		return (is_valid_direction(check_east, map_array, y, x + 1));
// 	return (false); //no valid direction found
// }

// static bool	validate_elevators(t_map *map)
// {
// 	int	**map_array;
// 	int	x;
// 	int	y;

// 	map_array = map->map_array;
// 	y = 0;
// 	while (y < map->height)
// 	{
// 		x = 0;
// 		while (x < map->height)
// 		{
// 			if (y > 0 && y < map->height - 1 && x > 0 && x < map->width - 1)
// 				if (map_array[y][x] == 2)
// 					if (!valid_elevator(map_array, y, x))
// 					{
// 						set_error("Invalid elevator");
// 						return (false);
// 					}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (true);
// }

/* ************************************************************************** */

// // Directional offsets: North, South, East, West
// int	dy[] = {-1, 1, 0, 0};
// int	dx[] = {0, 0, 1, -1};

// // check if the elevator is correctly placed
// static bool	is_valid_position(int **map_array, int y, int x, int rows, int cols)
// {
// 	// Check boundaries
// 	if (x < 1 || x >= cols - 1 || y < 1 || y >= rows - 1)
// 		return (false);

// 	int	direction = 0;
// 	while (direction < 4)
// 	{
// 		int	new_y = y + dy[direction];
// 		int	new_x = x + dx[direction];

// 		// count zeros and ones around current position
// 		int	zeros = 0;
// 		int ones = 0;
// 		int	i = 0;
// 		while (i < 4)
// 		{
// 			int	check_y = new_y + dy[i];
// 			int	check_x = new_x + dx[i];
// 			if (check_y >= 0 && check_y < rows && check_x >= 0 && check_x < cols)
// 			{
// 				zeros += (map_array[check_y][check_x] == 0);
// 				ones += (map_array[check_y][check_x] == 1);
// 			}
// 			i++;
// 		}
// 		// if exactly one zero and three 1, check next position
// 		if (zeros == 1 && ones == 3)
// 		{
// 			// checking new space in front of elevator entrance
// 			int	front_y = new_y + dy[direction];
// 			int	front_x = new_x + dx[direction];
// 			// **need to find a way to simplify this in helper function ?
// 			if (map_array[frontY][frontX] == 1 && 
// 				map_array[frontY + dy[(direction + 1) % 4]][frontX + dx[(direction + 1) % 4]] == 1 &&
// 				map_array[frontY + dy[(direction + 3) % 4]][frontX + dx[(direction + 3) % 4]] == 1)
// 				return (true); //valid entrance and next space
// 		}
// 		direction++;
// 	}
// 	return (false);
// }

// static bool	validate_elevators(t_map *map)
// {
// 	int	**map_array;
// 	int	x;
// 	int	y;

// 	map_array = map->map_array;
// 	y = 0;
// 	while (y < map->height)
// 	{
// 		x = 0;
// 		while (x < map->height)
// 		{
// 			if (y > 0 && y < map->height - 1 && x > 0 && x < map->width - 1)
// 				if (map_array[y][x] == 2)
// 					if (!valid_elevator(map_array, y, x, map->height, map->width))
// 					{
// 						set_error("Invalid elevator");
// 						return (false);
// 					}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (true);
// }

/* ************************************************************************** */

// static bool	check_surroundings(int **map_array, int y, int x, int dir)
// {
// 	int	zero_count = 0;
// 	int	one_count = 0;
// 	int	dirs[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // N, S, W, E
	
// 	int	i = 0;
// 	while (i < 4)
// 	{
// 		int	new_y = y + dirs[i][0];
// 		int	new_x = x + dirs[i][1];
// 		if (map_array[new_y][new_x] == 0)
// 			zero_count++;
// 		else if (map_array[new_y][new_x] == 1)
// 			one_count++;
// 		i++;
// 	}
// 	if (zero_count == 1 && one_count == 3)
// 	{
// 		// check if open space is in the opposite direction of the entry
// 		int	check_y = y + dirs[dir][0] * -1;
// 		int	check_x = x + dirs[dir][1] * -1;
// 		return (map[check_y][check_x] == 0);
// 	}
// 	return (false);
// }

// bool	valid_elevator(int **map, int y, int x, int dir)
// {
// 	if (dir == NO)
// 		return (check_surroundings(map_array, y, x, NO));
// 	if (dir == SO)
// 		return (check_surroundings(map_array, y, x, SO));
// 	if (dir == EA)
// 		return (check_surroundings(map_array, y, x, EA));
// 	if (dir == WE)
// 		return (check_surroundings(map_array, y, x, WE));
// 	return (false);
// }

/* ************************************************************************** */

static bool	check_north(int **map, int y, int x)
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

static bool	check_south(int **map, int y, int x)
{
	int	wall_count;
	int	valid;

	wall_count = 0;
	valid = map[y + 1][x] == 0;
	
	wall_count += map[y][x+1] == 1;
	wall_count += map[y][x-1] == 1;
	wall_count += map[y-1][x] == 1;
	return (valid && wall_count == 3);
}

static bool	check_east(int **map, int y, int x)
{
	int	wall_count;
	int valid;

	wall_count = 0;
	valid = map[y][x + 1] == 0;
	
	wall_count += map[y + 1][x] == 1;
	wall_count += map[y - 1][x] == 1;
	wall_count += map[y][x - 1] == 1;
	return (valid && wall_count == 3);
}

static bool check_west(int **map, int y, int x)
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

bool	valid_elevator(int **map, int y, int x)
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
