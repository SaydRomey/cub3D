/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:10 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/01 22:56:16 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "libft.h"
# include <math.h>
# include "animations.h"
# include "asset.h"
# include "cleanup.h"
# include "controls.h"
# include "draw.h"
# include "elevator.h"
# include "error.h"
# include "levels.h"
# include "map.h"
# include "math_utils.h"
# include "minimap.h"
# include "parsing.h"
# include "pixels.h"
# include "player.h"
# include "raycast.h"
# include "segworld.h"
# include "utils.h"
# include "validate.h"
# include "vfx.h"

# define GAME_TITLE "cub3D"

# ifndef BONUS
#  define BONUS 0
#  define MAP_CHARS	"01NSEW"
# else
#  define MAP_CHARS	"0123NSEW"
# endif // BONUS

# define CUB_FLOOR_PATH		"img/school/checker.png"
# define CUB_CEILING_PATH	"img/school/light.png"
# define CUB_EVALUATOR_PATH	"img/evaluator.png"
# define CUB_MENU_PATH		"img/ui/menu.png"

/* ************************************************************************** */

/*
used for checklist and errors
*/
typedef struct s_info
{
	bool	problem;
	char	*error_msg;
	bool	wall_check[WALL_TEXTURE_LEN];
	bool	color_check[COLOR_TYPE_LEN];
	bool	color_check_bonus[COLOR_TYPE_LEN];
	bool	found_direction;
}			t_info;

/*
*/
typedef struct s_cub
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*radar_img;
	t_list		*levels;
	int			current_level;
	int			chosen_level;
	t_elevator	elevator;
	t_player	player;
	t_keys		keys;
	t_mouse		mouse;
	t_raycast	raycast;
	t_vfx		vfx;
	char		*floor_ceiling_default[COLOR_TYPE_LEN];
	mlx_image_t	*user_img;
	mlx_image_t	*menu_img;
}				t_cub;

/* ************************************************************************** */

// info.c
t_info	*call_info(void);
void	free_info(void);
bool	there_is_a_problem(void);
void	reset_info(void);

// main.c
t_cub	*call_cub(void);

#endif // CUB3D_H
