#ifndef ELEVATOR_H
# define ELEVATOR_H

# define BUTTON_SIZE 		64
# define ELEVATOR_TEX_LEN	5

# define CLOSE				0
# define OPEN				1

# include "MLX42.h"
# include "utils.h"
# include "animations.h"
# include "levels.h"
# include "map.h"

enum elevator_id
{
	E_WALL,
	E_FLOOR,
	E_CEILING,
	E_BTN_OFF,
	E_BTN_ON
};

typedef struct s_button
{	
	mlx_image_t	*button_imgs[2];
	t_point		position;
	t_point		size;
	bool		state;
}				t_button;

typedef struct s_elevator
{
	t_point		position;
	int			orientation;
	mlx_image_t	*texture[ELEVATOR_TEX_LEN];
	t_animation	door_animation;
	bool		map_change;
	bool		door;
	bool		buttons_on;
	t_button	buttons[2]; // 0 = UP, 1 = DOWN
	int			id;
	bool		door_open;
}				t_elevator;

// elevator_init.c
t_elevator	init_elevator(t_level *lvl);

// elevator_events.c
void		elevator_events(void *param);
void		elevator_change_map(int lvl_index);

// elevator_buttons.c
void		check_button_hover(t_button btn[2]);
void		init_buttons(t_elevator *elevator);

// validate_elevator.c
int			get_elevator_orientation(int **map, t_point *position);
void		get_elevator_info(t_level *lvl, t_map *map);
bool		valid_elevator(int **map, int y, int x);

#endif // ELEVATOR_H
