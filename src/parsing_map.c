/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:55:33 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/04 12:19:45 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
horizontal validation
*/
static int	map_line_is_valid(char *cubline, bool *found_direction)
{
	char	*line;
	int		len;
	int		i;
	char	c;
	bool	valid = true;

	line = ft_strtrim(cubline, " \t\n");
	len = ft_strlen(line);
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
				if (*found_direction)
				{
					valid =  false;
					set_error("More than one directional character found in map");
					break;
				}
				*found_direction = true;
			}
			else if (c == '0' || (c == ' ' && i != len - 1))
			{
				if (i == 0 || line[i - 1] != '1' || (i < len - 1 && line[i + 1] != '1'))
				{
					valid = false;
					set_error("'0' or space not properly bordered by a '1'");
					break;
				}
			}
			else if (c != '1' && !ft_strchr("NSEW", c))
			{
				valid = false;
				set_error("Invalid character found in map");
				break;
			}
			i++; //or ++i ?
		}
	}
	free(line);
	return (valid);
}

/*
line */
static int	is_map_line(const char *line)
{
	int	has_non_space_map_char;
	
	if (!line || !*line)
		return (FALSE);
	has_non_space_map_char = FALSE;
	while (*line)
	{
		if (ft_strchr(MAP_CHARS, *line) && !ft_isspace(*line))
			has_non_space_map_char = TRUE;
		else if (!ft_isspace(*line))
			return (FALSE);
		line++;
	}
	return (has_non_space_map_char);
}

static int	is_wall_line(char *line)
{
	while (*line)
	{
		if (*line != '1' && !ft_isspace(*line))
			return (FALSE);
		line++;
	}
	return (TRUE);
}

/*
if is map line:
    if not yet in map and line is wall line
        set in_map to true,
        store the line
    else if in map (line can be a map line during the map)
        store the line
    else if not yet in map and line is not a wall line (but a map line)
        error: invalid first line of map portion
else
    if we are in map, but line is not a map line
        error: non-map line / invalid line in map portion
if we are in map and the line is a wall line
    we set in_map to false (*!! this is not the right way, as we can have wall lines inside map)
    */
void	parse_map_line(char *line, t_scene *scene)
{
	if (is_map_line(line))
	{
		if (!in_map() && is_wall_line(line))
		{
			set_in_map(true); // start of the map portion
			store_map_line(&scene->map_list, line);
		}
		else if (in_map())
		{
			store_map_line(&scene->map_list, line);
		}
		else if (!is_wall_line(line))
		{
			set_error("Invalid map first line");
		}
	}
	else
	{
		if (in_map())
			set_error("Non-map line found within the map section");
	}
	if (in_map() && is_wall_line(line))
		set_in_map(false); // end of the map portion
}

// add starting char validation (exactly one else invalid)

/*
if we are in map
    if line is not a map line
        error: non-map line
    else (if it is a map line)
        store the map line
        *(check for last line here? maybe not)
    
else (if not yet in map)
    if line is map line
        if it is a wall line
            set in_map to true
            store the line
        else
            error: invalid first map line
*/
void	parse_map_line(char *line, t_scene *scene)
{
	static bool	potential_end = false;
	
	if (in_map())
	{
		if (!is_map_line(line))
			set_error("Non-map line found within the map section");
		else
		{
			store_map_line(&scene->map_list, line);
			if (is_wall_line(line))
				set_in_map(false);
		}
	}
	else
	{
		if (is_map_line(line))
		{
			if (is_wall_line(line))
			{
				set_in_map(true);
				store_map_line(&scene->map_list, line);
			}
			else
				set_error("Invalid map first line");
		}
	}
}

