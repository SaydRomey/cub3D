/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:10 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/21 20:04:57 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ideas to check:
/*
boussole en haut, stripe a la skyrim?

*/

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "libft.h"
# include <math.h>
# include "cub3d_ced.h"
// # include "cub3d_oli.h"


# define PIXEL_SIZE	4
# define PI			3.1415926535

# define PLAYER_SIZE		10
# define PLAYER_SPEED		5
# define PLAYER_TURN_SPEED	5

typedef struct s_point
{
	float	x;
	float	y;
}			t_point;

typedef struct s_map
{
	int	tile_size;
	int	width;
	int	height;
	int	floor_color;
	int	ceiling_color;
	int	wall_tile_color;
	int	floor_tile_color;
}		t_map;

typedef struct s_player
{
	t_point	position;
	t_point	delta;
	t_point	respawn;
	float	angle;
	int		size;
	int		color;
	float	speed;
	float	turn_speed;
}			t_player;

typedef struct s_keys
{
	bool	esc;
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	up;
	bool	left;
	bool	down;
	bool	right;
	bool	m; //minimap toggle
	bool	p; //player icon style
	bool	backspace; //to reset player position
}			t_keys;

typedef struct s_cub
{
	mlx_t       *mlx;
	mlx_image_t *img; //main game image
	mlx_image_t *minimap_img; //minimap image (check if we move this in t_map struct?)
	// 
	t_player	player;
	t_keys		keys;
	t_map		minimap;
}   t_cub;

/* ************************************************************************** */

// draw.c
void	draw_line(mlx_image_t *img, t_point start, t_point end, int color);
void	draw_rectangle(mlx_image_t *img, t_point origin, t_point end, int color);
void	background(mlx_image_t *img, int color);
void	draw_circle(mlx_image_t *img, t_point origin, int radius, int color);
void	draw_triangle(mlx_image_t *img, t_point p1, t_point p2, t_point p3, int color);

// error.c
void    error(void);

// hooks.c
void	keyhooks(mlx_key_data_t data, void *param);
void	update(void *ptr);

// math_utils.c
float	degree_to_radian(int degree);
int	    fix_angle(int angle);
float	distance(t_point a, t_point b, float angle);

// minimap.c
t_map	init_map(void);
void	draw_tile(mlx_image_t *img, t_point origin, t_point size, int color);
void	draw_minimap(mlx_image_t *img, t_map *map);

// pixels.c
void	draw_pixel(mlx_image_t *img, int x, int y, int color);
t_u8	get_pixel(mlx_image_t *img, int x, int y);
void	put_img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y);

// player.c
t_player	init_player(t_point start, char direction);
void	update_player_position(t_cub *cub);
void	update_player_direction(t_cub *cub);
void	update_player(t_cub *cub);
void	draw_player(mlx_image_t *img, t_player *player);
void	draw_player2(mlx_image_t *img, t_player *player);


// utils.c
void	toggle(bool *choice);
void	clear_img(mlx_image_t *img);
void	cleanup(t_cub *cub);

#endif // CUB3D_H
