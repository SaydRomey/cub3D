/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:14:18 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/08 23:08:28 by cdumais          ###   ########.fr       */
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
