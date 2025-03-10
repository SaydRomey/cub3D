/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:37:51 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/06 17:49:22 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "MLX42.h"
# include "utils.h"
# include "map.h"

# define MINI_VOID_COL		0x42424200
# define MINI_WALK_COL		0xFFFFFFFF
# define MINI_WALL_COL		0x000000FF
# define MINI_DOOR_COL		0x0000FFFF
# define MINI_ELEV_COL		0xBEBBB8FF

# define RADAR_SIZE			300
# define RADAR_MARGIN		20
# define RADAR_FOV			45
# define RADAR_FRAME_COL	0x887251FF
# define RADAR_BG_COL		0x000000FF

typedef struct s_radar
{
	mlx_image_t	*img;
	t_fpoint	player_pos;
	t_fpoint	offset;
	t_fpoint	player_minimap;
	t_fpoint	center;
	int			radius;
	t_fpoint	top_left;
}				t_radar;

typedef struct s_minimap
{
	mlx_image_t	*img;
	bool		highlight_player_pos;
	int			tile_size;
	t_point		center;
	int			half_width;
	int			half_height;
	t_point		offset;
	int			colors[4];
}				t_minimap;

// minimap_draw.c
void		draw_minimap(t_minimap *mini, t_map *map);

// minimap_utils.c
void		set_minimap_colors(t_map *map, int *colors);

// minimap.c
t_minimap	init_minimap(t_map *map);

// radar_utils.c
void		radar_interference(mlx_image_t *img, t_fpoint origin, int radius);
void		draw_radar_frame(t_radar *radar);

// radar.c
void		draw_radar(t_minimap *mini);

#endif // MINIMAP_H
