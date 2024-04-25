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
	float		step_y;
	int			width;
	int			height;
}				t_texture;

// raycast_assets.c
void		draw_assets(float z_buffer[WIDTH]);

// raycast_dda.c
void		execute_dda_algo(t_raycast *r);

// raycast_floor.c
t_texture	get_texture_floor_info(mlx_image_t *texture);
void		draw_ceiling_floor(t_texture tex[4], int y);

// raycast_init.c
void		raycast(void);

// raycast_utils.c
int			check_hit(int map_y, int map_x);
void		get_ray_bounds(void);
t_line		get_stripe_data(float divider, int center, int limit);
float		rot_matrix(t_fpoint a, t_fpoint b);
t_point		update_texture_position(t_texture tex, t_fpoint pos);

// raycast_walls.c
void		draw_wall_stripe(t_point ray_pos, t_render *r, int x);

#endif // RAYCAST_H
