/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:37:51 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/24 19:33:17 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "MLX42.h"
# include "utils.h"
# include "minimap.h"
# include "map.h"
# include "player.h"

# define RADAR_SIZE		300
# define RADAR_MARGIN	20

/*	should we separate the calculation and rendering logic,
	to only calculate on level change, and render in each frame? **?

*/
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
	bool		visible;
	int			tile_size;
	t_point		center;
	int			half_width;
	int			half_height;
	t_point		offset;
}				t_minimap;

// minimap_draw.c
void		draw_minimap(t_minimap *mini, t_map *map);

// minimap.c
t_minimap	init_minimap(t_map *map);

// radar_utils.c
bool		player_is_in_elevator(t_player *player);

// radar.c
void		draw_radar(t_minimap *mini);
// void		draw_radar(t_minimap *mini, t_map *map, t_player *player);

#endif // MINIMAP_H
