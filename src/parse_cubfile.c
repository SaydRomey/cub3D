/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cubfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:21:44 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/18 16:28:20 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	extract_starting_position(t_scene *scene)
{
	t_list	*node;
	int		node_count;
	char	*found;

	if (!call_info()->found_direction)
	{
		set_error("Map is missing a starting position");
		return ;
	}
	node = scene->map_list;
	node_count = 0;
	while (node != NULL)
	{
		found = ft_strchr((char *)node->content, (char)scene->spawn_orientation);
		if (found)
		{
			scene->starting_position.x = found - (char *)node->content;
			scene->starting_position.y = node_count;
			break;
		}
		node = node->next;
		node_count++;
	}
}

/*
maybe add line count for error precision? (to display the problematic line in terminal ?)

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
	free(line);
	close(fd);
	extract_starting_position(&scene);
	return (scene);
}
