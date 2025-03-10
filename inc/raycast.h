/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:39:33 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/06 18:11:38 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "MLX42.h"
# include "utils.h"

typedef struct s_render
{
	float		wall_perp_dist;
	float		wall_hit_pos;
	bool		side;
}				t_render;

typedef struct s_raycast
{
	bool		ray_hits_opened_door;
	float		row_distance[HEIGHT / 2];
	float		z_buffer[WIDTH];
	t_point		step;
	t_point		ray_pos;
	t_point		ray_pos_door;
	t_fpoint	grid_dist;
	t_fpoint	length;
	t_fpoint	ray_dir;
	t_fpoint	ray_dir_min;
	t_fpoint	ray_dir_max;
	t_render	ray_door;
	t_render	ray;
}				t_raycast;

typedef struct s_texture
{
	mlx_image_t	*to_draw;
	t_point		pixel;
	float		pos_y;
	float		pos_x;
	float		step_y;
	float		step_x;
	int			width;
	int			height;
}				t_texture;

// raycast_assets.c
void		draw_assets(void *param);

// raycast_dda.c
void		execute_dda_algo(t_raycast *r);

// raycast_floor_draw.c
void		draw_floor_ceiling_row(t_texture tex[4], int y);

// raycast_floor.c
t_texture	get_texture_floor_info(mlx_image_t *texture);
void		draw_floor_ceiling_textures(void *param);

// raycast_init.c
void		raycast(void);

// raycast_utils.c
int			check_hit(int map_y, int map_x);
t_line		get_stripe_data(float divider, int center, int limit);
float		rot_matrix(t_fpoint a, t_fpoint b);
int			get_next_unit(t_raycast *r);
t_texture	get_texture_info(mlx_image_t *texture);

// raycast_walls.c
void		draw_wall_stripe(t_point ray_pos, t_render *r, int x);

#endif // RAYCAST_H
