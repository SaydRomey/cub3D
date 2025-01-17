/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:39:10 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/25 16:32:35 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H

# include "MLX42.h"

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
	bool	backspace;
	bool	leftshift;
	bool	leftcontrol;
	bool	m;
	bool	p;
	bool	r;
	bool	one;
	bool	two;
	bool	three;
}			t_keys;

// hooks.c
void	keyhooks(mlx_key_data_t data, void *param);
void	update_controls(void *param);

// mouse.c
void	set_mouse(void *param);

#endif // CONTROLS_H

/* ************************************************************************** */
/* ************************************************************************** */

/*
typedef enum keys
{
	MLX_KEY_SPACE			= 32,
	MLX_KEY_APOSTROPHE		= 39,
	MLX_KEY_COMMA			= 44,
	MLX_KEY_MINUS			= 45,
	MLX_KEY_PERIOD			= 46,
	MLX_KEY_SLASH			= 47,
	MLX_KEY_0				= 48,
	MLX_KEY_1				= 49,
	MLX_KEY_2				= 50,
	MLX_KEY_3				= 51,
	MLX_KEY_4				= 52,
	MLX_KEY_5				= 53,
	MLX_KEY_6				= 54,
	MLX_KEY_7				= 55,
	MLX_KEY_8				= 56,
	MLX_KEY_9				= 57,
	MLX_KEY_SEMICOLON		= 59,
	MLX_KEY_EQUAL			= 61,
	MLX_KEY_A				= 65,
	MLX_KEY_B				= 66,
	MLX_KEY_C				= 67,
	MLX_KEY_D				= 68,
	MLX_KEY_E				= 69,
	MLX_KEY_F				= 70,
	MLX_KEY_G				= 71,
	MLX_KEY_H				= 72,
	MLX_KEY_I				= 73,
	MLX_KEY_J				= 74,
	MLX_KEY_K				= 75,
	MLX_KEY_L				= 76,
	MLX_KEY_M				= 77,
	MLX_KEY_N				= 78,
	MLX_KEY_O				= 79,
	MLX_KEY_P				= 80,
	MLX_KEY_Q				= 81,
	MLX_KEY_R				= 82,
	MLX_KEY_S				= 83,
	MLX_KEY_T				= 84,
	MLX_KEY_U				= 85,
	MLX_KEY_V				= 86,
	MLX_KEY_W				= 87,
	MLX_KEY_X				= 88,
	MLX_KEY_Y				= 89,
	MLX_KEY_Z				= 90,
	MLX_KEY_LEFT_BRACKET	= 91,
	MLX_KEY_BACKSLASH		= 92,
	MLX_KEY_RIGHT_BRACKET	= 93,
	MLX_KEY_GRAVE_ACCENT	= 96,
	MLX_KEY_ESCAPE			= 256,
	MLX_KEY_ENTER			= 257,
	MLX_KEY_TAB				= 258,
	MLX_KEY_BACKSPACE		= 259,
	MLX_KEY_INSERT			= 260,
	MLX_KEY_DELETE			= 261,
	MLX_KEY_RIGHT			= 262,
	MLX_KEY_LEFT			= 263,
	MLX_KEY_DOWN			= 264,
	MLX_KEY_UP				= 265,
	MLX_KEY_PAGE_UP			= 266,
	MLX_KEY_PAGE_DOWN		= 267,
	MLX_KEY_HOME			= 268,
	MLX_KEY_END				= 269,
	MLX_KEY_CAPS_LOCK		= 280,
	MLX_KEY_SCROLL_LOCK		= 281,
	MLX_KEY_NUM_LOCK		= 282,
	MLX_KEY_PRINT_SCREEN	= 283,
	MLX_KEY_PAUSE			= 284,
	MLX_KEY_F1				= 290,
	MLX_KEY_F2				= 291,
	MLX_KEY_F3				= 292,
	MLX_KEY_F4				= 293,
	MLX_KEY_F5				= 294,
	MLX_KEY_F6				= 295,
	MLX_KEY_F7				= 296,
	MLX_KEY_F8				= 297,
	MLX_KEY_F9				= 298,
	MLX_KEY_F10				= 299,
	MLX_KEY_F11				= 300,
	MLX_KEY_F12				= 301,
	MLX_KEY_F13				= 302,
	MLX_KEY_F14				= 303,
	MLX_KEY_F15				= 304,
	MLX_KEY_F16				= 305,
	MLX_KEY_F17				= 306,
	MLX_KEY_F18				= 307,
	MLX_KEY_F19				= 308,
	MLX_KEY_F20				= 309,
	MLX_KEY_F21				= 310,
	MLX_KEY_F22				= 311,
	MLX_KEY_F23				= 312,
	MLX_KEY_F24				= 313,
	MLX_KEY_F25				= 314,
	MLX_KEY_KP_0			= 320,
	MLX_KEY_KP_1			= 321,
	MLX_KEY_KP_2			= 322,
	MLX_KEY_KP_3			= 323,
	MLX_KEY_KP_4			= 324,
	MLX_KEY_KP_5			= 325,
	MLX_KEY_KP_6			= 326,
	MLX_KEY_KP_7			= 327,
	MLX_KEY_KP_8			= 328,
	MLX_KEY_KP_9			= 329,
	MLX_KEY_KP_DECIMAL		= 330,
	MLX_KEY_KP_DIVIDE		= 331,
	MLX_KEY_KP_MULTIPLY		= 332,
	MLX_KEY_KP_SUBTRACT		= 333,
	MLX_KEY_KP_ADD			= 334,
	MLX_KEY_KP_ENTER		= 335,
	MLX_KEY_KP_EQUAL		= 336,
	MLX_KEY_LEFT_SHIFT		= 340,
	MLX_KEY_LEFT_CONTROL	= 341,
	MLX_KEY_LEFT_ALT		= 342,
	MLX_KEY_LEFT_SUPER		= 343,
	MLX_KEY_RIGHT_SHIFT		= 344,
	MLX_KEY_RIGHT_CONTROL	= 345,
	MLX_KEY_RIGHT_ALT		= 346,
	MLX_KEY_RIGHT_SUPER		= 347,
	MLX_KEY_MENU			= 348,
}	keys_t;
*/
