/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:10 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/17 13:01:11 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// change all colors to unsigned ?

// when fixing libft, add %f to ft_printf..

// TODO: add the build folder of mlx to git ignore

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "libft.h"
# include <math.h>

# define PIXEL_SIZE			4
# define PI					3.1415926535
# define ISO_ANGLE			0.523599

/* ************************************************************************** */

// https://imagecolorpicker.com/en
// https://htmlcolorcodes.com/

/* colors
*/
# define HEX_BLACK			0x000000FF
# define HEX_GRAY			0x424242FF
# define HEX_DGRAY			0x2A2A2AFF
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
// # define MAP_CHARS "0123NSEW"


typedef struct s_fpoint
{
	float	x;
	float	y;
}			t_fpoint;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_rgba
{
	int	r;
	int	g;
	int	b;
	int	a;
}		t_rgba;

t_rgba	int_to_rgba(int color);
int		rgba_to_int(t_rgba rgba);

// change these names/values later... (currently not using this..)
typedef enum e_map_elem
{
	OUTOFBOUND = -2,
	SPACE = -1,
	WALKABLE = 0,
	WALL = 1,
	DOOR = 2,
	ELEVATOR = 3,
}	t_map_elem;

// do we add them in parsing?
// we could have default textures, overridable by definition in .cub file ?
# define F	4
# define C	5
# define I	6

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
	char	*error_msg;
	
	// parsing checklist
	bool	wall_check[WALL_TEXTURE_LEN];
	bool	color_check[COLOR_TYPE_LEN];
	bool	found_direction;

	// for testing
	bool	print_proof; //for proof() and vaproof()
	t_u32	grayscale; //tmp test
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
	bool	enabled; //state

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
	bool	spacebar; //to open elevators
	bool	backspace; //to reset player position
	bool	leftshift; //to speedup
	bool	leftcontrol;
	bool	m; //minimap toggle
	bool	p; //player icon style
	bool	one;
	bool	two;
	bool	three;
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
	bool			speedup;
	// 
	int				size; //in minimap
	int				color; //in minimap
	struct s_player	*respawn;
}					t_player;

/* ************************************************************************** */

# define TILE_SIZE 42

// typedef struct s_options
// {
// 	bool	dynamic_tile_size; //1
// 	bool	round; //2
// 	bool	rectangular; //!2
// 	bool	visible; //m
// }			t_options;

// typedef struct s_minimap
// {
// 	mlx_image_t	*img;
// 	mlx_image_t	*round_img;
// 	// 
// 	int			tile_size;
// 	int			radius;
// 	t_point		center;
// 	// 
// 	t_options	options;
// }				t_minimap;

typedef struct s_minimap
{
	mlx_image_t	*img;
	int			tile_size;

	// mlx_image_t *radar;
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

/* ************************************************************************** */
typedef struct s_shadow
{
	bool	enabled;
	float	density;
	float	max;

	// bool	flashlight; maybe a class itself, with enabled(on/off), range, light color, battery level?
}			t_shadow;

typedef struct s_fog
{
	bool	enabled;
	int		color;
	float	density;
	float	max;
}			t_fog;

typedef struct s_vfx
{
	bool	textures_enabled; //add a separate flag for floor/celing ?
	
	
	t_shadow	shadow;
	
	bool	shadow_enabled;
	float	shadow_intensity; //?
	float	shadow_min; //?
	float	shadow_max; //?
	
	
	t_fog	fog;
	
	bool	fog_enabled; //fog effect on walls, floor and ceiling **(if no textures, adapt draw_floor and draw_ceiling)
	int		fog_color;
	bool	floor_fog_enabled; //fog effect on floor and a portion of walls *(can exist without 'fog_enabled also)
	float	floor_fog_level; //defines how high on the wall the floor fog goes [0.0f is none, 1.0f is all the way up]
	int		floor_fog_color;
	
}			t_vfx;

typedef struct s_cub
{
	mlx_t       *mlx;
	mlx_image_t *img;
	// 
	mlx_image_t	*texture[7]; //change to have this in t_map
	// 
	t_map		map;
	t_minimap	mini;
	t_player	player;
	t_raycast	raycast;
	t_keys		keys;
	t_mouse		mouse;
	t_vfx		vfx;
}   			t_cub;

/* ************************************************************************** */
// call.c
t_cub	*call_cub(void);
void	call_clean(void);
int		**call_array(void);
int		call_width(void);
int		call_height(void);

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

// fog.c
int		fog_effect(int color, float raw_dist, float min, float max, int fog_color);
int		fog_effect2(int color, float distance); //to test
int		shadow_effect(int color, float raw_dist, float min, float max);
int		apply_shadow(int color, float shadow_factor); //to test
int		apply_bright(int color, float bright_factor); //to test


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
bool	is_in_circle(t_point point, t_point center, int radius);
int		ft_clamp(int value, int min, int max);
float	ft_fclamp(float value, float min, float max);
float	ft_lerp(float a, float b, float t);

// minimap.c
t_minimap	init_minimap(t_cub *cub);
void		draw_minimap(t_minimap *mini, t_map *map);
// 
void		iso_test(t_minimap *mini);
void		iso_grid(t_minimap *mini);

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
int		combine_rgba(int r, int g, int b, int a);
int		get_pixel(mlx_image_t *img, int x, int y);
void	put_img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y);
int		rgb_to_int(int r, int g, int b);
int		get_color(t_scene *scene, int id);
int		get_red(int color);
int		get_green(int color);
int		get_blue(int color);
int		get_alpha(int color);

// player.c
t_player	init_player(t_scene *scene);
// void	update_player_position(t_cub *cub);
// void	update_player_direction(t_cub *cub);
void	update_player(t_cub *cub);

// raycast.c
int		check_hit(int map_y, int map_x);
void	draw_ceiling_floor(t_cub *cub, int y);
void	draw_wall_stripe(t_cub *cub, int x);
void	execute_dda_algo(t_player *p, t_raycast *r);
void	raycast(t_cub *cub);

// test.c
void	proof(char *str);
void	vaproof(char *str, ...);
void	test_scene(t_scene scene);
void    test_map(t_map map);
void	test_term_colors(void);
void	grayscale_test(t_cub *cub);

void	print_2d_array(int **array, int height, int width);

// utils.c
mlx_image_t *load_png(char *filepath, mlx_t *mlx);
mlx_image_t	*new_img(mlx_t *mlx, t_u32 width, t_u32 height, bool visible);
void		extract_wall_textures(t_scene *scene, t_map *map, mlx_t *mlx);
void		cleanup_wall_textures(t_map *map);
// 
void	toggle(bool *choice);
void	clear_img(mlx_image_t *img);
void	fill_img(mlx_image_t *img, unsigned int grayscale);
void	move_img(mlx_image_t *img, int x, int y);

// validate.c
void	validate_arguments(int argc, char **argv);
void	validate_scene(t_scene *scene);
void	validate_map(t_map *map);

// vfx.c
void	update_vfx(t_vfx *vfx);
void	wall_vfx(int *color, float distance, float tex_pos_y);
void	floor_ceiling_vfx(int *color[2], float distance);




#endif // CUB3D_H
