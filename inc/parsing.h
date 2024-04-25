/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:46:26 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/24 19:24:46 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "utils.h"

/*
used to parse the cubfiles and organize text data
*/
typedef struct s_scene
{	
	char		*wall_textures[WALL_TEXTURE_LEN];
	char		*floor_ceiling_textures[COLOR_TYPE_LEN];
	char		*colors[COLOR_TYPE_LEN][RGB_LEN];
	t_list		*map_list;
	char		spawn_orientation;
	t_fpoint	starting_position;
}				t_scene;

// parse_cubfile.c
t_scene	parse_cubfile(char *filepath);

// parse_floor_ceiling.c
void	parse_floor_ceiling(char *cubline, t_scene *scene);

// parse_map.c
void	parse_map_line(char *line, t_scene *scene);

// parse_walls.c
void	parse_wall_texture(char *cubline, t_scene *scene);

// validate_scene.c
void	validate_scene(t_scene *scene);

#endif // PARSING_H
