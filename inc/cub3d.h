/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:10 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/03 21:39:25 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// change all colors to unsigned ?

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "libft.h"
# include <math.h>

# ifndef BONUS
#  define BONUS 0
# endif

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

# define SCENE_LIMIT		5

// # define MAP_CHARS "01NSEW"
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

// do we add them in parsing?
// we could have default textures, overridable by definition in .cub file ?
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
	char	*test_msg; //to test reset_info() later...
}			t_info;

t_info	*call_info(void);
void	free_info(void);
bool    there_is_a_problem(void);
void	reset_info(void);

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

# define NUMSPRITES 2

typedef struct s_asset
{
	float		distance;
	t_fpoint	position;
}				t_asset;

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

typedef struct s_scene
{	
	char		*wall_textures[WALL_TEXTURE_LEN]; //change to 'wall_texture_paths[]'?
	// add floor ceiling texture paths
	
	char		*colors[COLOR_TYPE_LEN][RGB_LEN];
	t_list		*map_list;
	char		spawn_orientation;
	t_fpoint	starting_position;
}				t_scene;

# define TILE_SIZE 42

typedef struct s_minimap
{
	mlx_image_t	*img;
	
	int			tile_size;
	t_point		center;
	int			half_width;
	int			half_height;

}				t_minimap;

typedef struct s_map
{
	int			height;
	int			width;
	int			**map_array; //2d array for the map
	 
	int			floor_color;
	int			ceiling_color;
	
	mlx_image_t	*wall_textures_img[WALL_TEXTURE_LEN];
	// mlx_image_t	*floor_ceiling_img[2]; //check if we put all in one img array ?

	char		spawn_orientation;
	t_fpoint	starting_position;
}		t_map;

typedef struct s_level
{
	char		*filepath;
	int			index; //to navigate to 'lvl->index + 1' for next floor..
	
	t_map		map;
	t_minimap	minimap;
	
}			t_level;

typedef struct s_cub
{
	mlx_t       *mlx;
	mlx_image_t *img;

	t_list		*levels;
	int			current_level; //gets init to 0 with init_cub()

	t_player	player;
	
	t_raycast	raycast;
	
	t_keys		keys;
	t_mouse		mouse;
	
	t_vfx		vfx;
}   			t_cub;

// typedef struct s_cub
// {
// 	mlx_t       *mlx;
// 	mlx_image_t *img;
// 	// 
// 	mlx_image_t	*texture[6]; //change to have this in t_map //make it so they are default or parsed
// 	int			scene_total;
// 	//
// 	t_asset		*assets;
// 	t_elevator	elevator;
// 	t_map		*map;
// 	t_map		*maps;
// 	t_minimap	mini;
// 	t_player	player;
// 	t_raycast	raycast;
// 	t_keys		keys;
// 	t_mouse		mouse;
// 	t_vfx		vfx;
// }   			t_cub;

/* ************************************************************************** */
// assets.c
t_asset	*init_assets(void);

// animation.c
t_animation	set_animation(mlx_image_t *img);
void		update_animation(t_animation *a, bool direction);

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

// door.c
void	update_door_texture(t_cub *cub);

// draw.c
void	draw_line(mlx_image_t *img, t_fpoint start, t_fpoint end, int color);
void	draw_rectangle(mlx_image_t *img, t_fpoint origin, t_fpoint end, int color);
void	draw_ceiling(mlx_image_t *img, int color);
void	draw_floor(mlx_image_t *img, int color);
void	draw_background(mlx_image_t *img, int color);
void	draw_circle(mlx_image_t *img, t_fpoint origin, int radius, int color);
void	draw_triangle(mlx_image_t *img, t_fpoint p1, t_fpoint p2, t_fpoint p3, int color);

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
void	set_error_arg(char *str, char *arg); //broken ?
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

// level.c
// void	add_new_level(t_list **levels, t_map map, char *filepath); //this one is with the deep copy of a map init in main
void	add_new_level(t_list **levels, t_scene scene, char *filepath);


void	delete_level(void *level);
t_level	*get_level(t_list *levels, int index);
t_map	*get_map(t_list *levels, int index);

// map.c
t_map	init_map(t_scene *scene);
void	store_map_line(t_list **map_list, char *line);
int		get_map_width(t_list *map_list);
bool	is_wall_line(char *line);
void	free_map(int **map, int height);
int 	**allocate_grid(int height, int width);
int		**get_2d_map(t_list *map_list, int height, int width);

// math_utils.c
float	degree_to_radian(int degree);
int	    fix_angle(int angle);
bool	is_in_circle(t_point point, t_point center, int radius);
int		ft_clamp(int value, int min, int max);
float	ft_fclamp(float value, float min, float max);
float	ft_lerp(float a, float b, float t);

// minimap.c
t_minimap	init_minimap(t_map *map);
void		draw_minimap(t_minimap *mini);

// mouse.c
void	set_mouse(t_cub *cub);

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
// t_player	init_player(t_scene *scene);
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

// scene.c
void	retrieve_scene(t_cub *cub, char *filepath);

// segworld.c
void	call_segworld(t_cub *cub, t_elevator *e, t_fpoint pos, int ori);

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
