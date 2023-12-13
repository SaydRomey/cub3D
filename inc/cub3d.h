/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:22:13 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/12 19:28:29 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "cub3d_utils.h"
// # include "mlx.h"
# include <math.h>

typedef struct s_point
{
	float		x;
	float		y;
	// int			z;
	int			color;
}				t_point;

typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_mlx
{
	char		*title;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;	
}				t_mlx;


void	clear_image(t_img *img);
void	draw_pixel(t_img *img, int x, int y, int color);
void	draw_line(t_mlx *mlx_struct, t_point start, t_point end);



#endif
