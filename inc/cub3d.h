/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:22:13 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/19 18:59:55 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "cub3d_utils.h"
# include "mlx.h"
# include <math.h>

# include "key_linux.h"

typedef struct s_point
{
	float		x;
	float		y;
}				t_point;

typedef struct s_map
{
	int			tile_size;
	int			width;
	int			height;
	int			floor_color;
	int			ceiling_color;
	int			wall_tile_color;
	int			floor_tile_color;
}				t_map;

typedef struct s_player
{
	t_point		position;
	t_point		delta;
	float		angle;
	int			size;
	int			color;
	float		speed;
	float		turn_speed;
	float		mouse_turn_speed;
}				t_player;

typedef struct s_keys
{
	int			esc;
	int			w;
	int			a;
	int			s;
	int			d;
	int			up;
	int			left;
	int			down;
	int			right;
}		t_keys;

typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_cub
{
	char		*title;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_player	player;
	t_keys		keys;
	t_map		map;
	// 
	t_point		cursor;
	t_point		prev_cursor;
	// 
	int			info_switch; //to display info in terminal
	int			line_switch; //tmp test to display mouse-player line
	// 
	t_point		horizon; //test to look up and down with mouse
}				t_cub;

// cleanup.c (tmp until src are explicitly defined in makefile)
int			terminate_mlx(t_cub *cub);

// draw_shapes.c
// 
void		draw_circle(t_img *img, t_point origin, int radius, int color);
void		draw_circle_hollow(t_img *img, t_point origin, int radius, int thickness, int color);
void		draw_tile(t_img *img, t_point origin, t_point size, int color);
void		draw_triangle(t_img *img, t_point p1, t_point p2, t_point p3, int color);
// void		draw_rect(t_img *img, t_point origin, t_point end, int color);

// draw_utils.c
// 
void		clear_image(t_img *img);
void		color_background(t_img *img, int floor_color, int ceiling_color);
void		draw_pixel(t_img *img, int x, int y, int color);
void		draw_line(t_img *img, t_point start, t_point end, int color);

// hooks.c
// 
int			key_press(int keycode, t_cub *cub);
int			key_release(int keycode, t_cub *cub);
void		check_options(t_cub *cub);
int			update_game(void *param);
int			key_print(int key, t_cub *cub); //tmp

// math_utils.c
// 
float		degree_to_radian(int degree);
int			fix_angle(int angle);

// minimap.c
// 
t_map		init_map(void);
void		draw_mini_map(t_img *img, t_map *map);

// mouse.c
// 
int			moving_left(t_cub *cub);
int			moving_right(t_cub *cub);
int			follow_mouse(int mouse_x, int mouse_y, void *param);
void		draw_cursor(t_img *img, t_cub *cub);
int			read_mouse(int button, int mouse_x, int mouse_y, void *param);

// player.c
// 
t_player	init_player(t_point start);
void		draw_player(t_img *img, t_player *player);
void		update_player_position(t_cub *cub);
void		update_player_direction(t_cub *cub);

// render.c
// 
void		render(t_cub *cub);

// utils.c
// 
int			mlx_text(t_cub *cub, char *str, int x, int y);
void		proof(char *msg);
void		toggle(int *toggle);
int			spawning_orientation(char direction);
int			is_in_the_zone(t_point to_verify, t_point origin, t_point end);
int			is_in_window(t_point to_verify);

#endif
