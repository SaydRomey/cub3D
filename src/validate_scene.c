/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:56:05 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/01 15:11:22 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
check for first and last lines of the map
*/
static bool	is_wall_line(char *line)
{
	while (*line)
	{
		if (*line != '1' && !ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}

static void	check_walls(void)
{
	int	i;

	i = 0;
	while (i < WALL_TEXTURE_LEN)
	{
		if (!call_info()->wall_check[i])
		{
			set_error("Missing wall texture path");
			break ;
		}
		i++;
	}
}

static void	check_colors(void)
{
	if (!call_info()->color_check[FLOOR])
		set_error("Missing floor color");
	else if (!call_info()->color_check[CEILING])
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
}
