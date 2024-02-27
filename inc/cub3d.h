/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:10 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/27 18:04:30 by cdumais          ###   ########.fr       */
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

# define PIXEL_SIZE	4

/* colors */ //need to check these...

// https://imagecolorpicker.com/en
// https://htmlcolorcodes.com/

# define HEX_GROUND			0x8E8849FF
# define HEX_SKY			0x6DC0C3FF

# define HEX_BLACK			0x000000FF
# define HEX_GRAY			0x404040FF
# define HEX_WHITE			0xFFFFFFFF
# define HEX_RED			0xFF0000FF
# define HEX_GREEN			0x00FF00FF
# define HEX_BLUE			0x0000FFFF
# define HEX_YELLOW			0xFFFF00FF
# define HEX_MAGENTA		0xFF00FFFF //bright on mac
# define HEX_CYAN			0x00FFFFFF

# define HEX_ORANGE 		0xFF7700FF //best orange on mac
# define HEX_ORANGEY		0xED840CFF //between orange and yellow on mac
# define HEX_PURPLE			0x800080FF //weak on MAC
# define HEX_OLILAS			0xA27CF1FF //bluish purple on mac
# define HEX_PINK			0xFFC0CBFF //pale pink on mac
# define HEX_BROWN			0x663300FF //weak dark orange on mac

# define HEX_OLIVE      0x808000FF

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
	int	**map_array; //2d array for the map

	int	width;
	int	height;
	int	tile_size;
	int	floor_color;
	int	ceiling_color;
	int	wall_tile_color;
	int	floor_tile_color;
	int	background_color;
}		t_map;

typedef struct s_player
{
	t_point			position;
	t_point			delta;
	float			angle;
	int				size;
	int				color;
	float			speed;
	float			turn_speed;
	struct s_player	*respawn;
}					t_player;

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

/* ************************************************************************** */

// in map section
enum point_type
{
	EMPTY_SPACE,
	WALL,
	PLAYER
};

typedef struct s_map_point
{
	int				x;
	int				y;
	enum point_type	point_type;
}					t_map_point;

# define WALL_TEXTURE_LEN 4 //change name later

enum wall_id
{
	NO,
	SO,
	EA,
	WE
};

# define COLOR_TYPE_LEN 2

enum color_id
{
	FLOOR,
	CEILING
};

# define RGB_LEN 3

enum rgb_id
{
	R,
	G,
	B
};

# define MAP_CHARS "01NSEW"

typedef struct s_scene
{
	// parse_cubfile
	char	*wall_textures[WALL_TEXTURE_LEN]; //maybe change for mlx_texture_t ?
	char	*colors[COLOR_TYPE_LEN][RGB_LEN];

	t_list	*map_list;

	// validate_scene
	int		floor;
	int		ceiling;
	
	t_point	starting_position;	
	char	spawn_orientation;
}			t_scene;

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

// bres_line.c
void	bres_line(mlx_image_t *img, t_point start, t_point end, int color);

// draw.c
void	draw_line(mlx_image_t *img, t_point start, t_point end, int color);
void	draw_rectangle(mlx_image_t *img, t_point origin, t_point end, int color);
void	draw_ceiling(mlx_image_t *img, int color);
void	draw_floor(mlx_image_t *img, int color);
void	draw_background(mlx_image_t *img, int color);
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
t_map	init_map(t_scene *scene);
void	draw_tile(mlx_image_t *img, t_point origin, t_point size, int color);
void	draw_minimap(mlx_image_t *img, t_map *map);

// parsing.c
t_scene	parse_cubfile(char *filepath);

// pixels.c
void	draw_pixel(mlx_image_t *img, int x, int y, int color);
int		get_pixel(mlx_image_t *img, int x, int y);
void	put_img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y);

// player.c
t_player	init_player(t_point start, char direction);
void	update_player_position(t_cub *cub);
void	update_player_direction(t_cub *cub);
void	update_player(t_cub *cub);
void	draw_player(mlx_image_t *img, t_player *player);
void	draw_player2(mlx_image_t *img, t_player *player);


// utils.c
int		rgb_to_int(int r, int g, int b);
int		get_color(t_scene *scene, int id);
// 
void	toggle(bool *choice);
void	clear_img(mlx_image_t *img);
void	cleanup(t_cub *cub);

#endif // CUB3D_H
