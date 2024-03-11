/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:10 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/10 16:21:30 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "libft.h"
# include <math.h>

# define PIXEL_SIZE			4
# define PI					3.1415926535

/* ************************************************************************** */

// https://imagecolorpicker.com/en
// https://htmlcolorcodes.com/

/* colors
*/
# define HEX_BLACK			0x000000FF
# define HEX_GRAY			0x404040FF
# define HEX_WHITE			0xFFFFFFFF
# define HEX_RED			0xFF0000FF
# define HEX_GREEN			0x00FF00FF
# define HEX_BLUE			0x0000FFFF
# define HEX_YELLOW			0xFFFF00FF
# define HEX_MAGENTA		0xFF00FFFF //bright on mac
# define HEX_CYAN			0x00FFFFFF
// 
# define HEX_ORANGE 		0xFF7700FF //best orange on mac
# define HEX_ORANGEY		0xED840CFF //between orange and yellow on mac
# define HEX_PURPLE			0x800080FF //weak on MAC
# define HEX_OLILAS			0xA27CF1FF //blueish purple on mac
# define HEX_PINK			0xFFC0CBFF //pale pink on mac
# define HEX_BROWN			0x663300FF //weak dark orange on mac
# define HEX_OLIVE      	0x808000FF
// 
# define HEX_GROUND			0x8E8849FF
# define HEX_SKY			0x6DC0C3FF
/* ************************************************************************** */

/* player
*/
# define PLAYER_FOV			0.80
# define PLAYER_SIZE		10
# define PLAYER_SPEED		0.1
# define PLAYER_TURN_SPEED	0.1

/* textures (do we need this or we use a TILE_SIZE or something like this?)
*/
# define TEX_WIDTH			64
# define TEX_HEIGHT			64
// # define TEX_WIDTH			256
// # define TEX_HEIGHT			256

# define MAP_HEIGHT	10
# define MAP_WIDTH	10

# define CLOSE				0
# define OPEN				1

# define DOOR_DISTANCE		1
# define DOOR_CHAR			2

/* lengths of enums
*/
# define WALL_TEXTURE_LEN	4
# define COLOR_TYPE_LEN 	2
# define RGB_LEN			3

# define MAP_CHARS "01NSEW"

typedef struct s_fpoint
{
	float	x;
	float	y;
}			t_fpoint;

typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

// change these names/values later...
typedef enum e_map_elem
{
	SPACE = -1,
	ACCESSIBLE = 0,
	WALL = 1,
	DOOR = 2
}	t_map_elem;

// # define NO					0
// # define SO					1
// # define WE					2
// # define EA					3
# define F					4
# define C					5
# define I					6

enum wall_id
{
	NO,
	SO,
	EA,
	WE
};

enum color_id
{
	FLOOR,
	CEILING
};

enum rgb_id
{
	R,
	G,
	B
};

/* ************************************************************************** */

/*
used for checklist and errors
*/
typedef struct s_info
{
	bool	problem;
	bool	wall_check[WALL_TEXTURE_LEN];
	bool	color_check[COLOR_TYPE_LEN];
	bool	found_direction;

	// int		mlx_errno;
	char	*error_msg;
	// 
	unsigned int	grayscale; //tmp test
	// 
}			t_info;

t_info	*call_info(void);
void	free_info(void);
bool    there_is_a_problem(void);
/* ************************************************************************** */

typedef struct s_line
{
	int		height;
	int		start;
	int		end;
}			t_line;

typedef struct s_raycast
{
	float		wall_perp_dist;
	float		wall_hit_pos;
	bool		door;
	bool		side;
	t_point		step;
	t_point		ray_pos;
	t_fpoint	grid_dist;
	t_fpoint	length;
	t_fpoint	ray_dir;
	t_fpoint	ray_dir_min;
	t_fpoint	ray_dir_max;
}				t_raycast;

typedef struct s_texture
{
	mlx_image_t	*to_draw;
	t_point		pixel;
	float		pos_y;
	float		step_y;
}				t_texture;

typedef struct s_mouse
{
	bool	left;
	bool	right;
	float	rotate_x;
}			t_mouse;

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

typedef struct s_player
{
	t_fpoint		position;
	char			spawn_orientation;
	// 
	t_fpoint		delta;
	t_fpoint		cam_plane;
	float			angle;
	float			fov;
	float			speed;
	float			turn_speed;
	// 
	int				size; //in minimap
	int				color; //in minimap
	struct s_player	*respawn;
}					t_player;

typedef struct s_minimap
{
	mlx_image_t	*img;
	mlx_image_t	*round_img;
	// 
	int			tile_size;
	// 
}				t_minimap;

typedef struct s_map
{
	int			height;
	int			width;
	int			**map_array; //2d array for the map
	// 
	int			floor_color;
	int			ceiling_color;
	mlx_image_t	*wall_textures_img[WALL_TEXTURE_LEN];
}		t_map;

typedef struct s_scene
{
	char		*wall_textures[WALL_TEXTURE_LEN]; //change to 'wall_texture_paths[]'?
	char		*colors[COLOR_TYPE_LEN][RGB_LEN];
	t_list		*map_list;
	char		spawn_orientation;
	t_fpoint	starting_position;
}				t_scene;

typedef struct s_cub
{
	mlx_t       *mlx;
	mlx_image_t *img;
	// 
	mlx_image_t	*texture[7]; //change to have this in t_map
	// 
	t_map		map;
	t_minimap	minimap;
	t_player	player;
	t_raycast	raycast;
	t_keys		keys;
	t_mouse		mouse;
}   			t_cub;

/* ************************************************************************** */

// cleanup.c
void	cleanup_scene(t_scene *scene);
void	cleanup_map(t_map *map);
void	cleanup(t_cub *cub);

// draw.c
void	draw_line(mlx_image_t *img, t_fpoint start, t_fpoint end, int color);
void	draw_rectangle(mlx_image_t *img, t_fpoint origin, t_fpoint end, int color);
void	draw_ceiling(mlx_image_t *img, int color);
void	draw_floor(mlx_image_t *img, int color);
void	draw_background(mlx_image_t *img, int color);
void	draw_circle(mlx_image_t *img, t_fpoint origin, int radius, int color);
void	draw_triangle(mlx_image_t *img, t_fpoint p1, t_fpoint p2, t_fpoint p3, int color);

// error.c
void	set_error(char *str);
void	set_error_arg(char *str, char *arg);
char	*get_error(void);
void    error(void);
void	parsing_error(char *line, int fd, t_scene *scene);
void	error_mlx(void);

// hooks.c
void	keyhooks(mlx_key_data_t data, void *param);
void	update(void *ptr);

// map.c
t_map	init_map(t_scene *scene);
void	store_map_line(t_list **map_list, char *line);
int		get_map_width(t_list *map_list);
bool	is_wall_line(char *line);
void	free_map(int **map, int height);
int		**get_2d_map(t_list *map_list, int height, int width);

// math_utils.c
float	degree_to_radian(int degree);
int	    fix_angle(int angle);
int		is_inside_circle(t_fpoint to_check, t_fpoint circle_center, int radius);
float	distance(t_fpoint a, t_fpoint b, float angle);

// minimap.c
t_minimap	init_minimap(t_cub *cub);
void	draw_minimap(t_minimap *minimap, t_map *map);

// mouse.c
void	set_mouse(t_cub *cub);
void	cursor_hook(double xpos, double ypos, void *param);

// parsing_floor_ceiling.c
void	parse_floor_ceiling(char *cubline, t_scene *scene);

// parsing_map.c
void	parse_map_line(char *line, t_scene *scene);

// parsing_walls.c
void	parse_wall_texture(char *cubline, t_scene *scene);

// parsing.c
t_scene	parse_cubfile(char *filepath);

// pixels.c
void	draw_pixel(mlx_image_t *img, int x, int y, int color);
int		get_pixel(mlx_image_t *img, int x, int y);
void	put_img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y);

// player.c
t_player	init_player(t_scene *scene);
// void	update_player_position(t_cub *cub);
// void	update_player_direction(t_cub *cub);
void	update_player(t_cub *cub);

// raycast.c
// int		check_hit(int map_y, int map_x);
int		check_hit2(int map_y, int map_x, int **map_array); //tmp
void	draw_ceiling_floor(t_cub *cub, int y);
void	draw_wall_stripe(t_cub *cub, int x);
// void	execute_dda_algo(t_player *p, t_raycast *r);
void	execute_dda_algo(t_player *p, t_raycast *r, int **map_array);
void	raycast(t_cub *cub);

// test.c
void	proof(char *str);
void	test_scene(t_scene scene);
void    test_map(t_map map);
void	test_term_colors(void);
void	grayscale_test(t_cub *cub);

void	print_2d_array(int **array, int height, int width);

// utils.c
mlx_image_t *load_png(char *filepath, mlx_t *mlx);
mlx_image_t	*new_img(mlx_t *mlx, t_u32 width, t_u32 height, bool visible);
void		extract_wall_textures(t_scene *scene, t_map *map, mlx_t *mlx);
// 
int		rgb_to_int(int r, int g, int b);
int		get_color(t_scene *scene, int id);
// 
void	toggle(bool *choice);
void	clear_img(mlx_image_t *img);
void	fill_img(mlx_image_t *img, unsigned int grayscale);




// validate.c
void	validate_arguments(int argc, char **argv);
void	validate_scene(t_scene *scene);

// call.c
t_cub	*call_cub(void);
void	call_clean(void);
int		**call_array(void);
int		call_width(void);
int		call_height(void);


#endif // CUB3D_H
