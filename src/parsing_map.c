/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:55:33 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/04 17:51:37 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
checks if 'line' has only allowed map characters: "01 NSEW"
and a character other than a space
*/
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
		if (ft_strchr("01NSEW", line[i]))
			has_valid_char = true;
		else if (!ft_isspace(line[i]))
			return (false);
		i++;
	}
	return (has_valid_char);
}

static bool	check_contour(const char *line, int i)
{
	char	current;
	char	prev;
	char	next;
	
	current = line[i];
	if (i > 0)
		prev = line[i - 1];
	else
		prev = '\0';
	next = line[i + 1];
	if (current == '0' || current == ' ')
	{
		if ((prev == '1' || prev == current || ft_strchr("NSEW", prev)) && 
			(next == '1' || next == current || ft_strchr("NSEW", next)))
			return (true);
		else
			return (false);
	}
	else if (ft_strchr("NSEW", current))
	{
		if ((prev == '1' || prev == '0') && (next == '1' || next == '0'))
			return (true);
		else
			return (false);
	}
	return (true);
}

static bool map_line_is_valid(const char *line)
{
	int	len;
	int	i;

	len = ft_strlen(line);
	if (len < 1 || line[0] != '1' || line[len - 1] != '1')
		return (false);
	i = 0;
	while (line[i] != '\0')
	{
		if (!check_contour(line, i))
				return (false);
		i++;
	}
	return (true);	
}

void	scan_for_start(char *line, t_scene *scene)
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
				return;
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
	if (is_map_line(line)) //must have only valid chars from "01 NSEW"
	{
		if (map_line_is_valid(line))
		{
			store_map_line(&scene->map_list, cubline);
			scan_for_start(line, scene); //will set error if duplicate start
		}
		else
			set_error("Invalid map line");
	}
	free(line);
}

/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

/*
		// if (!check_contour(line, i, '0') || !check_contour(line, i, ' ') ||
		// 	!check_contour(line, i, 'N') || !check_contour(line, i, 'S') ||
		// 	!check_contour(line, i, 'E') || !check_contour(line, i, 'W'))

static bool	check_contour(const char *line, int i, char check_char)
{
	char	prev;
	char	next;

	if (line[i] != check_char)
		return (true); //skip if not the char we are checking
	if (i == 0 || line[i + 1] == '\0')
	{
		return (false);
	}
	prev = line[i - 1];
	next = line[i + 1];
	
	// '0' and ' ' must be contoured by same as them or a '1'
	if (check_char == '0' || check_char == ' ')
	{
		if ((prev == '1' || prev == check_char) && (next == '1' || next == check_char))
			return (true);
		return (false);
	}
	
	// for N,S,E,W contour must be '1' or '0'
	if ((prev == '1' || prev == '0') && (next == '1' || next == '0'))
		return (true);
	return (false);
}
*/

/*
static bool	map_line_is_valid(char *cubline)
{
	bool	valid;
	char	*line;
	int		len;
	int		i;
	char	c;

	valid = true;
	line = ft_strtrim(cubline, " \t\n");
	len = ft_strlen(line);

	// check first and last char of the trimmed line
	if (len < 1 || line[0] != '1' || line[len - 1] != '1')
		valid = false;
	else
	{
		i = 0;
		while (valid == true && i < len)
		{
			c = line[i];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (call_info()->found_direction)
				{
					valid = false;
					set_error("More than one starting point found in map");
					break;
				}
				call_info()->found_direction = true;
			}
			else if (c == '0')
			{
				if (line[i - 1] != '1' || line[i - 1] != '0' || line[i - 1] != '0' || line[i - 1] != '1')
				{
					valid = false;
					set_error("'0' character not properly bordered by a '1'");
					break;
				}
			}
			i++;
		}
	}
	free(line)
	return (valid);
}
*/