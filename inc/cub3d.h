/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:22:13 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/29 22:09:45 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "cub3d_utils.h"
# include "mlx.h"
# include <math.h>

typedef struct s_point
{
	float		x;
	float		y;
}				t_point;

typedef struct s_player
{
	t_point		position;
	t_point		delta;
	float		angle;
	int			size; //?
	int			color;
	float		speed;
	float		turn_speed;
}				t_player;

typedef struct s_mouse
{
	t_point		cursor;
	t_point		prev_cursor;
	// delta !?
	// throttle ?
}				t_mouse;

// use t_bool instead ? since it is either '0' or '1' (no need for 32 bits...)
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
	// 
	// experimental elements
	char		*img_name;
	int			visible; // to conditionnaly put image to window
	// z_index
	// size param
// Event Handlers:
	// if making interactive elements, could include function pointers for event handlers (like click, hover) within struct.
// animations: For animated elements, might include properties for animation, like frame count, current frame, animation speed, etc.
// Grouping or Tags: To manage related images (like UI elements belonging to the same panel), could include a tag or group ID.
	
}				t_img;

typedef struct	s_mlx
{
	char	*title;
	void	*mlx_ptr;
	void	*win_ptr;
}			t_mlx;

typedef struct s_cub
{
	t_mlx		mlx; // holds mlx handle, window handle, and window title
	t_list		*img_lst; // test and implement this !! (linked list of each images)
	t_player	player;
	t_keys		keys;
}				t_cub;



#endif
