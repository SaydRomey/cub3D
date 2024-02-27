/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:21:44 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/27 18:38:24 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// #include "parsing.h"

static void	parse_wall_texture(char *line, t_scene *scene)
{
	char	*wall[4];
	int		id;

	wall[0] = "NO ";
	wall[1] = "SO ";
	wall[2] = "EA ";
	wall[3] = "WE ";
	id = 0;
	while (id < WALL_TEXTURE_LEN)
	{
		if (ft_strncmp(line, wall[id], 3) == SAME)
		{
			// add check if wall texture is already set
			scene->wall_textures[id] = ft_strdup(line + 3);
			return;
		}
		id++;
	}
	return;
}

static void	parse_floor_ceiling(char *line, t_scene *scene)
{
	char	*colors[2];
	char	**split; //rgb
	int		id;

	colors[0] = "F ";
	colors[1] = "C ";
	id = 0;
	while (id < COLOR_TYPE_LEN)
	{
		if (ft_strncmp(line, colors[id], 2) == SAME)
		{
			split = ft_split(line + 2, ',');
			int	i = 0;
			while (i < RGB_LEN) //implement a check_split(split, RGB_LEN) function ?
			{
				if (split[i] == NULL)
				{
					// error: missing color component
					break;
				}
				scene->colors[id][i] = ft_strtrim(split[i], " ");
				i++;
			}
			free_split(split);
		}
		id++;
	}
	return;
}

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

t_scene	parse_cubfile(char *filepath)
{
	t_scene	scene;
	int		fd;
	char	*line;
	char	*trimmed_line;

	ft_memset(&scene, 0, sizeof(t_scene));
	fd = open(filepath, READ);
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
		{
			ft_printf("map->%s", line);
			ft_lstadd_back(&scene.map_list, ft_lstnew(ft_strdup(line)));
		}
		else
		{
			trimmed_line = ft_strtrim(line, " \t\n");
			parse_wall_texture(trimmed_line, &scene);
			parse_floor_ceiling(trimmed_line, &scene);
			free(trimmed_line);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (scene);
}

/*
static int	is_wall_line(char *line)
{
	while (*line)
	{
		if (*line != '1' && *line != ' ')
			return (FALSE);
		line++;
	}
	return (TRUE);
}

t_scene	parse_cubfile(char *filepath)
{
	t_scene	scene;
	int		fd;
	char	*line;
	char	*trimmed_line;

	ft_memset(&scene, 0, sizeof(t_scene));
	fd = open(filepath, READ);
	line = get_next_line(fd);
	int	line_count = 1; //tmp
	while (line)
	{
		ft_printf("%d-> %s", line_count, line);
		if (is_wall_line(line))
		{
			ft_printf("wall_line [%d]\n", line_count); //tmp
			// parse map content (implement later)
		}
		trimmed_line = ft_strtrim(line, " \t\n");
		parse_wall_texture(trimmed_line, &scene);
		parse_floor_ceiling(trimmed_line, &scene);
		
		
		free(trimmed_line);
		free(line);
		line = get_next_line(fd);
		line_count++;
	}
	free(line);
	close(fd);
	
	return (scene);
}
*/

