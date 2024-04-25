/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/24 19:01:53 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "MLX42.h"
# include "libft.h"

/* lengths of enums
*/
# define WALL_TEXTURE_LEN	4
# define COLOR_TYPE_LEN 	2
# define RGB_LEN			3

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

/*
used in raycasting and in t_asset
*/
typedef struct s_line
{
	int		size;
	int		start;
	int		end;
}			t_line;

enum e_map_elem
{
	OUTOFBOUND = -2,
	SPACE = -1,
	WALKABLE = 0,
	WALL = 1,
	DOOR = 2,
	ELEVATOR = 3,
};

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

// utils_img.c
mlx_image_t	*new_img(mlx_t *mlx, t_u32 width, t_u32 height, bool visible);
mlx_image_t	*copy_img(mlx_image_t *src, mlx_t *mlx);
mlx_image_t *load_png(char *filepath, mlx_t *mlx);
void		clear_img(mlx_image_t *img);
void		move_img(mlx_image_t *img, int x, int y);

// utils.c
int		cardinal_to_radian(char cardinal);
void	toggle(bool *choice);
void	change_window_title(char *filepath);

#endif // UTILS_H
