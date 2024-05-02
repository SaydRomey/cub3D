/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:47:00 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/01 20:09:40 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXELS_H
# define PIXELS_H

# include "MLX42.h"

// TODO: adjust color hex values with following websites:

// https://imagecolorpicker.com/en
// https://htmlcolorcodes.com/

# define PIXEL_SIZE		4

/* colors
*/
# define HEX_BLACK		0x000000FF
# define HEX_GRAY		0x424242FF
# define HEX_LGRAY		0xBEBBB8FF
# define HEX_DGRAY		0x2A2A2AFF
# define HEX_WHITE		0xFFFFFFFF
# define HEX_RED		0xFF0000FF
# define HEX_GREEN		0x00FF00FF
# define HEX_BLUE		0x0000FFFF
# define HEX_YELLOW		0xFFFF00FF
# define HEX_MAGENTA	0xFF00FFFF //bright on mac
# define HEX_CYAN		0x00FFFFFF
// 
# define HEX_OLILAS		0xA27CF1FF //blueish purple on mac
# define HEX_ORANGE 	0xFF7700FF //best orange on mac
# define HEX_PURPLE		0x800080FF //weak on MAC
# define HEX_PINK		0xFFC0CBFF //pale pink on mac
# define HEX_BROWN		0x663300FF //weak dark orange on mac
// 
# define HEX_GROUND		0x8E8849FF
# define HEX_SKY		0x6DC0C3FF

// pixel_color_utils.c
void	add_color_totals(int *totals, int color);
void	process_pixels(mlx_image_t *img, int *totals, int *count);
void	compute_averages(int *totals, int count, int *averages);

// pixel_colors.c
int		average_img_color(mlx_image_t *img);
int		average_color(int *colors, int n);
int		complement_color(int color);

// pixel_utils.c
int		combine_rgba(int r, int g, int b, int a);
int		get_red(int color);
int		get_green(int color);
int		get_blue(int color);
int		get_alpha(int color);

// pixels.c
void	draw_pixel(mlx_image_t *img, int x, int y, int color);
int		get_pixel(mlx_image_t *img, int x, int y);
int		random_pixel(int limit);
int		interference_pixel(void);

#endif // PIXELS_H
