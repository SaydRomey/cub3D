/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:21:44 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/26 22:20:48 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// #include "parsing.h"

/*

- scene description:

* except for map content,
each type of element can be seperated by one or more empty lines

* except for the map content which always has to be the last,
each type of element can be in any order in the file

* except for the map,
any type of information from an element
can be seperated by one or more space(s)

**? the map must be parsed as it looks in the file
spaces are a valid part of the map, and are up to us to handle **?

we must be able to parse any kind of map,
as long as it respects the rules of the map

- elements:

each element's first information is the **type identifier** (composed of one or two chars),
followed by all specific info for each opbject in a * strict order * such as:

	- textures:

NO ./path_to_the_north_texture

north texture:
	type identifier: NO
	path to the north texure: ./path_to_the_north_texture

SO ./path_to_the_south_texture

WE ./path_to_the_west_texture

EA ./path_to_the_east_texture

	- floor / ceiling

F 220,100,0

	type identifier: F
	R,G,B colors in range [0, 255] : 220(R), 100(G), 0(B)

C 225,30,0

Example of the mandatory part with a minimalist .cub scene:

NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

		1111111111111111111111111
		1000000000110000000000001
		1011000001110000000000001
		1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111


//

- the map content:

6 possible characters

0 for an empty space
1 for a wall

N, S, E, O for the player's starting position and spawning orientation


** if any kind of misconfiguration is ecountered, must exit properly and return

"Error\n"

followed by an explicit message of our choosing

error checks:

	map must be closed / surrounded by walls


implement functions that return a specific info, extracted from the file

*/

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
		trimmed_line = ft_strtrim(line, " \t\n");
		
		if (ft_strncmp(trimmed_line, "NO ", 3) == SAME)
			scene.wall_textures[NO] = ft_strdup(trimmed_line + 3);
		if (ft_strncmp(trimmed_line, "SO ", 3) == SAME)
			scene.wall_textures[SO] = ft_strdup(trimmed_line + 3);
		if (ft_strncmp(trimmed_line, "EA ", 3) == SAME)
			scene.wall_textures[EA] = ft_strdup(trimmed_line + 3);
		if (ft_strncmp(trimmed_line, "WE ", 3) == SAME)
			scene.wall_textures[WE] = ft_strdup(trimmed_line + 3);

		char	**split = NULL;
		char	*trimmed_color_str = NULL;
		
		if (ft_strncmp(trimmed_line, "F ", 2) == SAME)
		{			
			split = ft_split(trimmed_line + 2, ',');
			
			trimmed_color_str = ft_strtrim(split[0], " \t");
			scene.floor.r = ft_atoi(split[0]);
			free(trimmed_color_str);
			trimmed_color_str = ft_strtrim(split[1], " \t");
			scene.floor.g = ft_atoi(split[1]);
			free(trimmed_color_str);
			trimmed_color_str = ft_strtrim(split[2], " \t");
			scene.floor.b = ft_atoi(split[2]);
			free(trimmed_color_str);			
		}
		if (ft_strncmp(trimmed_line, "C ", 2) == SAME)
		{
			split = ft_split(trimmed_line + 2, ',');
			
			trimmed_color_str = ft_strtrim(split[0], " \t");
			scene.ceiling.r = ft_atoi(split[0]);
			free(trimmed_color_str);
			trimmed_color_str = ft_strtrim(split[1], " \t");
			scene.ceiling.g = ft_atoi(split[1]);
			free(trimmed_color_str);
			trimmed_color_str = ft_strtrim(split[2], " \t");
			scene.ceiling.b = ft_atoi(split[2]);
			free(trimmed_color_str);			
		}
		if (split)
			free_split(split);
		free(trimmed_line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);

	// validate_cubfile (make a checklist for each info, and detect invalid lines, colors, etc)
	
	// extract the info from the nodes, and place them in the struct
	// extract_cubfile_info(scene);
	
	// format the map part to a usable format for the raycaster
	// create_map_array(scene);


	return (scene);
}

// if (line_has_content(line))
// 			ft_lstadd_back(&scene.data, ft_lstnew(line));
// 			ft_printf("\033[32m%d\033[0m -> %s", i, line);
// 		else
// 			ft_printf("\033[31m%d\033[0m -> %s", i, line); //ignored line not added in the t_list
// 		// 
