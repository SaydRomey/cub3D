/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:33:35 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/29 15:38:15 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "MLX42.h"
# include "utils.h"
# include "libft.h"
# include "map.h"
# include "parsing.h"

typedef struct s_map
{
	int			height;
	int			width;
	int			**map_array;
	int			floor_color;
	int			ceiling_color;
	mlx_image_t	*wall_textures_img[WALL_TEXTURE_LEN];
	mlx_image_t	*floor_ceiling_img[COLOR_TYPE_LEN];
	char		spawn_orientation;
	t_fpoint	starting_position;
}				t_map;

// map_array.c
int		**allocate_grid(int height, int width);
int		**get_2d_map(t_list *map_list, int height, int width);

// map_list.c
void	store_map_line(t_list **map_list, char *line);
int		get_map_width(t_list *map_list);

// map_utils.c
bool	find_value_in_array(t_map *map, int value_to_find, t_point *point_ptr);
bool	has_duplicate(t_map *map, int value_to_find);

// map.c
int		get_color(t_scene *scene, int id);
t_map	init_map(t_scene *scene);

// validate_map.c
void	validate_map(t_map *map);

#endif // MAP_H
