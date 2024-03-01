/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:21:44 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/01 15:52:14 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_wall_texture(char *cubline, t_scene *scene)
{
	char	*wall[4];
	char	*line;
	int		id;

	wall[0] = "NO ";
	wall[1] = "SO ";
	wall[2] = "EA ";
	wall[3] = "WE ";
	line = ft_strtrim(cubline, " \t\n");
	id = 0;
	while (id < WALL_TEXTURE_LEN)
	{
		if (ft_strncmp(line, wall[id], 3) == SAME)
		{
			if (call_info()->wall_check[id])
				set_error("Duplicate wall texture definition");
			else
			{
				scene->wall_textures[id] = ft_strdup(line + 3);
				call_info()->wall_check[id] = true;
				ft_printf("%s is valid\n", line); //tmp
			}
		}
		id++;
	}
	free(line);
	return;
}

/* ************************************************************************** */

static void	split_rgb(int id, char *line, t_scene *scene)
{
	char	**split;
	int		i;

	split = ft_split(line + 2, ',');
	i = 0;
	while (i < RGB_LEN)
	{
		if (split[i] == NULL) // add check later for more than 3 values? (split[RGB_LEN + 1])
		{
			set_error("Missing color component");
			break;
		}
		scene->colors[id][i] = ft_strtrim(split[i], " ");
		ft_printf("color_id[%d], color_channel[%d] : %s\n", id, i, scene->colors[id][i]); //tmp
		i++;
	}
	call_info()->color_check[id] = true;
	free_split(split);
}

static void	parse_floor_ceiling(char *cubline, t_scene *scene)
{
	char	*colors[2];
	char	*line;
	int		id;

	colors[0] = "F ";
	colors[1] = "C ";
	line = ft_strtrim(cubline, " \t\n");
	id = 0;
	while (id < COLOR_TYPE_LEN)
	{
		if (ft_strncmp(line, colors[id], 2) == SAME)
		{
			if (call_info()->color_check[id])
			{
				set_error("Duplicate floor/ceiling color definition");
				break;
			}
			split_rgb(id, line, scene);
		}
		id++;
	}
	free(line);
	return;
}

/* ************************************************************************** */

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

static void	parse_map_line(char *line, t_scene *scene)
{
	if (is_map_line(line))
	{
		if (in_map() == false && is_wall_line(line))
			call_info()->in_map = true; // start of the map portion
		else if (in_map() == true && is_wall_line(line))
			call_info()->in_map = false; // end of the map portion
		if (in_map() || is_wall_line(line))
			store_map_line(&scene->map_list, line);
	}
	else if (in_map() == true)
		set_error("Non-map line found within the map section");
}

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
			parse_error(line, fd, &scene);
		
		parse_wall_texture(line, &scene);
		parse_floor_ceiling(line, &scene);
		parse_map_line(line, &scene);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	// 
	// int	i = 0;
	// while (i < WALL_TEXTURE_LEN)
	// {
	// 	if (!scene.checklist.wall[i])
	// 	{
	// 		// error: missing texture
	// 		ft_printf("error\n");
	// 	}
	// 	i++;
	// }
	// if (!scene.checklist.wall[FLOOR] || !scene.checklist.wall[CEILING])
	// {
	// 	// error: missing floor or ceiling color
	// 	ft_printf("error\n");
	// }
	// if (scene.map_list == NULL)
	// {
	// 	// error: no map data found
	// 	ft_printf("error\n");
	// }
	return (scene);
}


// t_scene	parse_cubfile(char *filepath)
// {
// 	t_scene	scene;
// 	int		fd;
// 	char	*line;
// 	char	*trimmed_line;

// 	ft_memset(&scene, 0, sizeof(t_scene));
// 	fd = open(filepath, READ);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (is_map_line(line))
// 		{
// 			// 
// 			if (scene.checklist.in_map == FALSE && is_wall_line(line))
// 				scene.checklist.in_map = TRUE; // start of the map portion
// 			else if (scene.checklist.in_map == FALSE && is_wall_line(line))
// 				scene.checklist.in_map = FALSE; // end of the map portion
			
// 			if (scene.checklist.in_map || is_wall_line(line))
// 			{
// 				ft_printf("map->%s", line);
// 				ft_lstadd_back(&scene.map_list, ft_lstnew(ft_strdup(line)));
// 			}
// 			else
// 			{
// 				// error: invalid map line (does 'is_map_line()' prevent this error ?)
// 				// or do we end up here if the first line is not only '1' and spaces..?
// 				ft_printf("error\n");
// 			}
// 		}
// 		else if (scene.checklist.in_map)
// 		{
// 			// error: non-map line found within map section
// 			ft_printf("error\n");
// 		}
// 		else
// 		{
// 			trimmed_line = ft_strtrim(line, " \t\n");
// 			parse_wall_texture(trimmed_line, &scene);
// 			parse_floor_ceiling(trimmed_line, &scene);
// 			free(trimmed_line);
// 		}
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	free(line);
// 	close(fd);
// 	// 
// 	int	i = 0;
// 	while (i < WALL_TEXTURE_LEN)
// 	{
// 		if (!scene.checklist.wall[i])
// 		{
// 			// error: missing texture
// 			ft_printf("error\n");
// 		}
// 		i++;
// 	}
// 	if (!scene.checklist.wall[FLOOR] || !scene.checklist.wall[CEILING])
// 	{
// 		// error: missing floor or ceiling color
// 		ft_printf("error\n");
// 	}
// 	if (scene.map_list == NULL)
// 	{
// 		// error: no map data found
// 		ft_printf("error\n");
// 	}
// 	return (scene);
// }



/*
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

