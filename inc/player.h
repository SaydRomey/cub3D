/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:25:21 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/01 19:02:14 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "utils.h"
# include "map.h"
# include "minimap.h"
# include "levels.h"

# define PLAYER_FOV			0.80
# define PLAYER_SIZE		24
# define PLAYER_SPEED		0.1
# define PLAYER_TURN_SPEED	0.1
# define PLAYER_COLOR		0x00FF00FF
# define PLAYER_ICON_ANGLE	30

typedef struct s_player
{
	t_fpoint		position;
	float			angle;
	float			fov;
	t_fpoint		delta;
	t_fpoint		cam_plane;
	float			speed;
	float			turn_speed;
	bool			speedup;
	int				size;
	int				color;
}					t_player;

// player_movement_utils.c
t_fpoint	get_velocity(t_player *player);
float		get_move_value(int x, int y, float rtn_value);
void		apply_rotation_matrix(t_fpoint *src, float turn_speed);
t_fpoint	rotate_vector_position(t_fpoint tmp, int rotation);
t_fpoint	rotate_vector_delta(t_fpoint tmp, int rotation);

// player_utils.c
bool		player_is_in_elevator(t_player *player);
void		draw_player(t_minimap *mini, t_player *player);

// player.c
void		update_player(t_player *player);
t_player	init_player(t_map *map, t_minimap *mini);

#endif // PLAYER_H
