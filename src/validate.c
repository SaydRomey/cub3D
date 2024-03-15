/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:14:18 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/14 05:18:05 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_arguments(int argc, char **argv)
{
	char	*extension;
	int		check;

	if (argc != 2)
	{
		va_exit_error("Usage: %s <filename>.cub", argv[0]);
	}
	extension = ft_strrchr(argv[1], '.');
	if (!extension)
		set_error("Missing extension");
	else if (ft_strncmp(extension, ".cub", 5) != SAME)
		set_error("Invalid file extension");
	else
	{
		check = read_check(argv[1]);
		if (check == 0)
			set_error_arg("File is empty", argv[1]);
		else if (check == -1)
			set_error_arg("Could not open or read", argv[1]); 
	}
	if (there_is_a_problem())
		error();
	proof("Valid args");
}

/* ************************************************************************** */

static void	check_walls(void)
{
	int	i;

	i = 0;
	while (i < WALL_TEXTURE_LEN)
	{
		if (!call_info()->wall_check[i])
		{
			set_error("Missing wall texture path");
			break;
		}
		i++;
	}
}

static void	check_colors(void)
{
	if (!call_info()->wall_check[FLOOR])
		set_error("Missing floor color");
	else if (!call_info()->wall_check[CEILING])
		set_error("Missing ceiling color");
}

static void	check_map(t_list *map_list)
{
	if (map_list)
	{
		if (!is_wall_line((char *)map_list->content))
			set_error("Invalid first map line");
		else if (!is_wall_line((char *)ft_lstlast(map_list)->content))
			set_error("Invalid last map line");
	}
	else
		set_error("No map data found");
}

/*
checks if we have parsed all required info from .cub file
(with the boolean checklist in t_info)

*/
void	validate_scene(t_scene *scene)
{
	check_walls();
	check_colors();
	check_map(scene->map_list);
	if (there_is_a_problem())
	{
		cleanup_scene(scene);
		error();
	}
	proof("Valid scene");
}

/* ************************************************************************** */

/*
11111111111
10000000001
10111111101
101 11  101
101 11  111
101101   11
100001    1
111111

** ' ' will be '-1' **

if [][] == '0', up must be 0 or 1 (or 2 or 3),
	down must be 0 or 1 (or 2 or 3)
if [][] == ' ', up must be ' ' or 1,
	down must be ' ' or 1
*/
static bool	check_vertical(int **map_array, int y, int x)
{
	int	current;
	int	up;
	int	down;
	
	current = map_array[y][x];
	up = map_array[y - 1][x];
	down = map_array[y + 1][x];

	if (current == 0) //EMPTY)
	{
		// if ((up == current || up == 1 || up == 2 || up == 3) &&	(down == current || down == 1 || down == 2 || down == 3))
		if (up >= current && down >= current)
			return (true);
		else
			return (false);
	}
	if (current == -1) //SPACE)
	{
		if ((up == current || up == 1 || up == -2) && (down == current || down == 1 || down == -2))
			return (true);
		else
			return (false);
	}
	return (true);
}

static bool	columns_are_valid(int **map_array, int width, int height)
{
	int	x;
	int	y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			if (y > 0 && y < height - 1) //don't check first and last line
				if (!check_vertical(map_array, y, x))
					return (false);		
			y++;
		}
		x++;
	}
	return (true);
}

void	validate_map(t_map *map)
{
	if (!columns_are_valid(map->map_array, map->width, map->height))
		set_error("Invalid array column");
	// 
	// valid elevator
	// valid doors
	// 
	if (there_is_a_problem())
	{
		cleanup_map(map);
		error();
	}
}
