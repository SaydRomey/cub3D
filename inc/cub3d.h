/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:22:13 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/15 20:26:10 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "cub3d_utils.h"
# include "mlx.h"
# include "key_linux.h"
# include <math.h>

# define WIDTH	600
# define HEIGHT	600

typedef struct s_point
{
	float		x;
	float		y;
	// int			z;
	// int			color;
}				t_point;

typedef struct s_map
{
	// t_point	origin;
	int		tile_size;
	int		map_x;
	int		map_y;
	int		bg_color;
	int		floor_color;
	int		wall_color;
	// 
}			t_map;

typedef struct s_player
{
	t_point	position;
	int		size;
	int		color;
	// 
}			t_player;

// 

typedef struct s_keys
{
	int	esc;
	int	w;
	int	a;
	int	s;
	int	d;
}		t_keys;

typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_cub
{
	char		*title;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_player	player;
	t_keys		keys;
	t_map		map;
}				t_cub;

// cleanup.c
int		terminate_mlx(t_cub *cub);

// draw_test.c
void	pixel_test(t_img *img);

// draw_utils.c
void	clear_image(t_img *img);
void	draw_pixel(t_img *img, int x, int y, int color);
void	draw_line(t_img *img, t_point start, t_point end, int color);
void	draw_rectangle(t_img *img, t_point origin, t_point end, int color);
void	draw_player(t_img *img, t_player *player);

// hooks.c
int		key_press(int keycode, t_cub *cub);
int		key_release(int keycode, t_cub *cub);
void	update_player_position(t_cub *cub);
void	check_options(t_cub *cub);
int		update_game(void *param);

// minimap.c
void	draw_mini_map(t_img *img, t_map *map);

// render.c
void	render(t_cub *cub);

// utils.c
int		mlx_text(t_cub *cub, char *str, int x, int y);
void	proof(char *msg);


#endif
