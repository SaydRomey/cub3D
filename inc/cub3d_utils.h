/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:43:19 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/17 17:01:56 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_UTILS_H
# define CUB3D_UTILS_H

// # ifdef __APPLE__
// #  include "../minilibx_macos/mlx.h"
// #  include "key_macos.h"
// #  define WIDTH 2560
// #  define HEIGHT 1395
// # else
// #  ifdef __linux__
// #   include "../minilibx_linux/mlx.h"
// #   include "key_linux.h"
// #   define WIDTH 1366
// #   define HEIGHT 768
// #  endif
// # endif

# include "key_linux.h" //(tmp)

// window with (tmp)
# define WIDTH	600
// window height (tmp)
# define HEIGHT	600

# define PLAYER_SIZE		10
# define PLAYER_SPEED		0.75
# define PLAYER_TURN_SPEED	2


# define PI 3.1415926535

/* bytes per pixel */
# define PIXEL_SIZE			4

/* hooks and events */
// 
# define KEY_PRESS			2
# define KEY_RELEASE		3
# define DESTROY			17
# define KEY_PRESS_MASK		(1L<<0)
# define KEY_RELEASE_MASK	(1L<<1)

/* colors */

# define HEX_BLACK			0x000000
// grays?
# define HEX_WHITE			0xFFFFFF
# define HEX_RED			0xFF0000
# define HEX_GREEN			0x00FF00
# define HEX_BLUE			0x0000FF
# define HEX_YELLOW			0xFFFF00
# define HEX_MAGENTA		0xFF00FF
# define HEX_CYAN			0x00FFFF
# define HEX_ORANGE			0xED840C
# define HEX_ORANGE2		0xFF7700
# define HEX_PURPLE			0x800080
# define HEX_OLILAS			0xA27CF1
# define HEX_LILAC			0xFF22FF
# define HEX_PINK			0xFFC0CB
# define HEX_BROWN			0xA52A2A

#endif
