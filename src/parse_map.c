/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:55:33 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/06 18:55:56 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_map_line(const char *line)
{
	int		i;
	bool	has_valid_char;

	if (!line || !*line)
		return (false);
	has_valid_char = false;
	i = 0;
	while (line[i])
	{
		if (ft_strchr(MAP_CHARS, line[i]))
			has_valid_char = true;
		else if (!ft_isspace(line[i]))
			return (false);
		i++;
	}
	return (has_valid_char);
}

/*
for each map square, validates its horizontal neighbouring spaces

*/
static bool	check_contour(const char *line, int i)
{
	char	*walkable;
	char	current;
	char	prev;
	char	next;

	if (BONUS)
		walkable = "03NSEW";
	else
		walkable = "0NSEW";
	current = line[i];
	prev = '\0';
	if (i > 0)
		prev = line[i - 1];
	next = line[i + 1];
	if (current == '0')
		return ((prev == '1' || ft_strchr(walkable, prev)) \
		&& (next == '1' || ft_strchr(walkable, next)));
	else if (current == ' ')
		return ((prev == '1' || prev == current) \
		&& (next == '1' || next == current));
	else if (ft_strchr("NSEW", current))
		return ((prev == '1' || prev == '0') \
		&& (next == '1' || next == '0'));
	return (true);
}

/*
checks if first and last map squares are walls
*(after having trimmed leading and trailing spaces)
also checks for valid contours for each values
*/
static bool	map_line_is_valid(const char *line)
{
	int	len;
	int	i;

	len = ft_strlen(line);
	if (len < 1 || line[0] != '1' || line[len - 1] != '1')
		return (false);
	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_strchr(MAP_CHARS, line[i]) && !ft_isspace(line[i]))
			return (false);
		if (!check_contour(line, i))
			return (false);
		i++;
	}
	return (true);
}

/*
sets the spawn orientation in scene
also sets the boolean flag 'found_direction'
*/
static void	scan_for_start(char *line, t_scene *scene)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_strchr("NSEW", line[i]))
		{
			if (call_info()->found_direction)
			{
				set_error("More than one starting point found in map");
				return ;
			}
			else
			{
				call_info()->found_direction = true;
				scene->spawn_orientation = line[i];
			}
		}
		i++;
	}
}

void	parse_map_line(char *cubline, t_scene *scene)
{
	char	*line;

	line = ft_strtrim(cubline, " \t\n");
	if (is_map_line(line) || call_info()->in_map == true)
	{
		call_info()->in_map = true;
		if (map_line_is_valid(line))
		{
			store_map_line(&scene->map_list, cubline);
			scan_for_start(cubline, scene);
		}
		else
			set_error("Invalid map line");
	}
	free(line);
}
