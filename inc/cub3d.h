/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:10 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/10 16:24:39 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "libft.h"
# include <math.h>

# ifndef BONUS
#  define BONUS 0
# endif

# define GAME_TITLE "cub3D"

/* tmp to display debug messages
*/
// # define PRINT_PROOF		0
# define PRINT_PROOF		1

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
// define other default colors (minimap)

/* ************************************************************************** */

/* player
*/
# define PLAYER_FOV			0.80
# define PLAYER_SIZE		10
# define PLAYER_SPEED		0.1
# define PLAYER_TURN_SPEED	0.1

# define MAP_HEIGHT			10
# define MAP_WIDTH			10

# define CLOSE				0
# define OPEN				1

# define DOOR_DISTANCE		1
# define DOOR_CHAR			2

/* lengths of enums
*/
# define WALL_TEXTURE_LEN	4
# define COLOR_TYPE_LEN 	2
# define RGB_LEN			3

# define MAP_CHARS "0123NSEW"

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

# define ELEVATOR 3

// remove when we can parse them, and implement default texture paths..
# define F	0
# define C	1
# define I	2
# define J	3

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

/* ************************************************************************** */

# define FRAME_SPEED	100
# define GO_LEFT		1
# define GO_RIGHT		0

typedef struct s_animation
{
	mlx_image_t	**frames;
	double		accumulator;
	int			frame_speed;
	int			current_frame;
	int			last_frame;
}				t_animation;

typedef struct s_slice
{
	int			total;
	int			width;
	int			height;
	t_point		position;
}				t_slice;

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

	// bonus and extra parsing
	bool	color_check_bonus[COLOR_TYPE_LEN]; //for floor and ceiling textures
	
	bool	found_elevator; //? (need to check how it is currently parsed...)

}			t_info;

/* ************************************************************************** */
/* ************************************************************************** */

# define NUMSPRITES 2

typedef struct s_asset
{
	float		distance;
	t_fpoint	position;
}				t_asset;

/* ************************************************************************** */
/* ************************************************************************** */

typedef struct s_line
{
	int		height;
	int		start;
	int		end;
}			t_line;

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

/* ************************************************************************** */
/* ************************************************************************** */

typedef struct s_mouse
{
	bool	enabled;

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
	
	bool	spacebar;
	bool	backspace; //to reset player position //might be too complex..
	bool	leftshift; //to speedup
	bool	leftcontrol;
	
	bool	m; //minimap toggle
	bool	p; //player icon style
	bool	one;
	bool	two;
	bool	three;
}			t_keys;

/* ************************************************************************** */

# define ELEVATOR_TEX_LEN	5

enum elevator_id
{
	E_WALL,
	E_FLOOR,
	E_CEILING,
	E_BTN_OFF,
	E_BTN_ON
};

typedef struct s_elevator
{
	int			id;
	bool		door;
	bool		door_open;
	bool		map_change;
	bool		valid;
	int			orientation;
	// t_point		orientation_vector;
	t_point		position;
	t_point		buttons_size;
	//
	t_animation	door_animation;
	mlx_image_t	*texture[ELEVATOR_TEX_LEN];
	mlx_image_t	*buttons;
}				t_elevator;

/* ************************************************************************** */
/* ************************************************************************** */

typedef struct s_player
{
	t_fpoint		position;
	float			angle;
	float			fov;
	
	t_fpoint		delta;
	t_fpoint		cam_plane;
	float			speed;
	float			turn_speed;
	// 
	bool			speedup;
	// 
	int				size; //in minimap
	int				color; //in minimap
	
}					t_player;

/* ************************************************************************** */

/*
used to parse the cubfiles and organize text data
*/
typedef struct s_scene
{	
	char		*wall_textures[WALL_TEXTURE_LEN]; //change to 'wall_texture_paths[]'?
	char		*floor_ceiling_textures[COLOR_TYPE_LEN];
	char		*colors[COLOR_TYPE_LEN][RGB_LEN];
	t_list		*map_list;
	char		spawn_orientation;
	t_fpoint	starting_position;
}				t_scene;

typedef struct s_minimap
{
	mlx_image_t	*img;
		
	int			tile_size;
	t_point		center;
	int			half_width;
	int			half_height;
	
	t_point		offset;

}				t_minimap;

typedef struct s_map
{
	int			height;
	int			width;
	int			**map_array;
	 
	int			floor_color;
	int			ceiling_color;
	
	mlx_image_t	*wall_textures_img[WALL_TEXTURE_LEN];
	mlx_image_t	*floor_ceiling_img[COLOR_TYPE_LEN];

	char		spawn_orientation;
	t_fpoint	starting_position;
}		t_map;

typedef struct s_level
{
	char		*filepath;
	int			index;
	
	t_map		map;
	t_minimap	mini;

	// t_elevator	elevator;
	int			e_orientation;
	t_point		e_position;

}			t_level;


typedef struct s_cub
{
	mlx_t       *mlx;
	mlx_image_t *img;
	char		*floor_ceiling_default[2];

	t_list		*levels;
	int			current_level; //gets init to 0 with init_cub()
	// int			chosen_level; //?maybe, to check if a level change request was triggered by an elevator event ?

	t_player	player;
	t_minimap	mini;
	
	t_raycast	raycast;
	t_elevator	elevator; //should there be one of these per level, or does it transcend ?
	
	t_keys		keys;
	t_mouse		mouse;
	
	t_vfx		vfx;
}   			t_cub;

/* ************************************************************************** */

// animation.c
t_animation	set_animation(mlx_image_t *img);
void		update_animation(t_animation *a, bool direction);

// call.c
t_cub	*call_cub(void);
void	call_clean(void); //tmp

// cleanup.c
void	cleanup_scene(t_scene *scene);
void	free_map_array(int **map_array, int height); //put a generic version of this in libft..
void	cleanup_map(t_map *map);
void	cleanup(t_cub *cub);

// draw.c
void	draw_line(mlx_image_t *img, t_fpoint start, t_fpoint end, int color);
void	draw_rectangle(mlx_image_t *img, t_fpoint origin, t_fpoint end, int color);
void	draw_floor(mlx_image_t *img, int color);
void	draw_ceiling(mlx_image_t *img, int color);
void	draw_background(mlx_image_t *img, int color);

void	draw_triangle(mlx_image_t *img, t_fpoint p1, t_fpoint p2, t_fpoint p3, int color);
void	draw_circle(mlx_image_t *img, t_fpoint origin, int radius, int color);

// elevator.c
t_elevator	init_elevator(t_cub *cub);
void		draw_buttons(t_elevator *elevator, int floor_number);
void		elevator_events(t_cub *cub);
void		parse_elevator(t_map *map, t_elevator *elevator);
void		change_map(t_cub *cub);
void		check_for_map_change(t_cub *cub, int y);
void		update_elevator_struct(t_cub *cub, t_elevator elevator);

// error.c
void	set_error(char *str);
void	set_error_arg(char *str, char *arg); //broken ? to test
char	*get_error(void);
void    error(void);
void	error_arg(char *arg); //tmp
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

// img_utils.c
mlx_image_t	*new_img(mlx_t *mlx, t_u32 width, t_u32 height, bool visible);
mlx_image_t	*copy_img(mlx_image_t *src, mlx_t *mlx);
mlx_image_t *load_png(char *filepath, mlx_t *mlx);

void		clear_img(mlx_image_t *img);
void		fill_img(mlx_image_t *img, unsigned int grayscale);
void		move_img(mlx_image_t *img, int x, int y);

void		put_img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y);

// info.c
t_info	*call_info(void);
void	free_info(void);
bool    there_is_a_problem(void);
void	reset_info(void);

// level.c
void	change_level(int index);

void	add_new_level(t_list **levels, t_map map, char *filepath); //this one is with the deep copy of a map init in main
void	delete_level(void *level);

t_level	*get_level(int index);
t_map	*get_map(int index);

// map_array.c
int 	**allocate_grid(int height, int width);
int		**get_2d_map(t_list *map_list, int height, int width);

// map_list.c
void	store_map_line(t_list **map_list, char *line);
int		get_map_width(t_list *map_list);
bool	is_wall_line(char *line);

// map.c
t_map	init_map(t_scene *scene);

// math_utils.c
float	degree_to_radian(int degree);
int	    fix_angle(int angle);
bool	is_in_circle(t_point point, t_point center, int radius);
float	ft_lerp(float a, float b, float t);

// minimap.c
void		draw_minimap(t_minimap *mini, t_map *map);
t_minimap	init_minimap(t_map *map);

// mouse.c
void	set_mouse(t_cub *cub);

// parse_cubfile.c
t_scene	parse_cubfile(char *filepath);

// parse_floor_ceiling.c
void	parse_floor_ceiling(char *cubline, t_scene *scene);

// parse_map.c
void	parse_map_line(char *line, t_scene *scene);

// parse_walls.c
void	parse_wall_texture(char *cubline, t_scene *scene);

// pixels.c
void	draw_pixel(mlx_image_t *img, int x, int y, int color);

int		combine_rgba(int r, int g, int b, int a);
int		get_pixel(mlx_image_t *img, int x, int y);

int		get_red(int color);
int		get_green(int color);
int		get_blue(int color);
int		get_alpha(int color);

int		rgb_to_int(int r, int g, int b);
int		get_color(t_scene *scene, int id);

// player.c
t_player	init_player(t_map *map);
// void	update_player_position(t_cub *cub);
// void	update_player_direction(t_cub *cub);
void	update_player(t_cub *cub);

// raycast.c
int		check_hit(int map_y, int map_x);
t_point	update_texture_position(t_texture tex, t_fpoint pos);
// void	draw_assets(t_cub *cub, float z_buffer[NUMSPRITES]);
void	draw_assets(t_cub *cub, float z_buffer[WIDTH]);
void	draw_ceiling_floor(t_cub *cub, int y);
void	draw_wall_stripe(t_cub *cub, t_point ray_pos, t_render *r, int x);
void	execute_dda_algo(t_cub *cub, t_raycast *r);
void	raycast(t_cub *cub);

// segworld.c
// void	call_segworld(t_cub *cub, t_elevator *e, t_fpoint pos, int ori);

// test.c
void	proof(char *str);
void	cproof(char *str, char *color);
void	vaproof(char *str, ...);

void	test_scene(t_scene scene);
void    test_map(t_map map);
void	test_player(t_player player);

// utils.c
void	toggle(bool *choice);
void	change_window_title(char *filepath);

// validate_elevator.c
bool	valid_elevator(int **map, int y, int x);

// validate.c
void	validate_arguments(int argc, char **argv);

void	validate_scene(t_scene *scene);

void	validate_map(t_map *map);

// vfx.c
// void	update_vfx(t_vfx *vfx);
// void	wall_vfx(int *color, float distance, float tex_pos_y);
// void	floor_ceiling_vfx(int *color[2], float distance);

#endif // CUB3D_H
