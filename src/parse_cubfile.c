/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cubfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:21:44 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/07 21:04:35 by cdumais          ###   ########.fr       */
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

/*
checks if we have parsed all required info from .cub file
*/
static bool	checklist(t_scene *scene)
{
	int		i;

	i = 0;
	while (i < WALL_TEXTURE_LEN)
	{
		if (!call_info()->wall_check[i])
			return (set_error("Missing wall texture"), false);
		i++;
	}
	if (!call_info()->wall_check[FLOOR])
		return (set_error("Missing floor color"), false);
	if (!call_info()->wall_check[CEILING])
		return (set_error("Missing ceiling color"), false);
	if (scene->map_list)
	{
		if (!is_wall_line((char *)scene->map_list->content))
			return (set_error("Invalid first map line"), false);
		if (!is_wall_line((char *)ft_lstlast(scene->map_list)->content))
			return (set_error("Invalid last map line"), false);
	}
	else
		return (set_error("No map data found"), false);
	if (!call_info()->found_direction)
		return (set_error("Map is missing a starting position"), false);
	return (true);
}

static void	extract_starting_position(t_scene *scene)
{
	t_list	*node;
	int		node_count;
	char	*found;

	node = scene->map_list;
	node_count = 0;
	while (node != NULL)
	{
		found = ft_strchr((char *)node->content, (char)scene->spawn_orientation);
		if (found)
		{
			// int	pos_x = found - (char *)node->content;
			// int	pos_y = node_count;
			// ft_printf("X:%d Y:%d\n", pos_x, pos_y);
			// 
			scene->starting_position.x = found - (char *)node->content;
			scene->starting_position.y = node_count;
			// ft_printf("starting pos x: %d\n", (int)scene->starting_position.x);
			// ft_printf("starting pos y: %d\n", (int)scene->starting_position.y);
			break;
		}
		node = node->next;
		node_count++;
	}
}

/*
maybe add line count for error precision?

*/
t_scene	parse_cubfile(char *filepath)
{
	t_scene	scene;
	int		fd;
	char	*line;
	
	ft_memset(&scene, 0, sizeof(t_scene));
	fd = open(filepath, READ);
	line = get_next_line(fd);
	while (line)
	{
		if (there_is_a_problem())
			parsing_error(line, fd, &scene);
		parse_wall_texture(line, &scene);
		parse_floor_ceiling(line, &scene);
		parse_map_line(line, &scene);
		free(line);
		line = get_next_line(fd);
	}
	if (!checklist(&scene)) //maybe move this at the end, so parsing_error() does not need to close fd and free line...?
		parsing_error(line, fd, &scene);
	free(line);
	close(fd);
	extract_starting_position(&scene);
	return (scene);
}
