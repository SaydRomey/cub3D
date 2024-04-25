/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:47:00 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/24 19:25:03 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXELS_H
# define PIXELS_H

// TODO: adjust color hex values with following websites:

// https://imagecolorpicker.com/en
// https://htmlcolorcodes.com/

# define PIXEL_SIZE		4

/* colors
*/
# define HEX_BLACK		0x000000FF
# define HEX_GRAY		0x424242FF
# define HEX_DGRAY		0x2A2A2AFF
# define HEX_WHITE		0xFFFFFFFF
# define HEX_RED		0xFF0000FF
# define HEX_GREEN		0x00FF00FF
# define HEX_BLUE		0x0000FFFF
# define HEX_YELLOW		0xFFFF00FF
# define HEX_MAGENTA	0xFF00FFFF //bright on mac
# define HEX_CYAN		0x00FFFFFF
// 
# define HEX_ORANGE 	0xFF7700FF //best orange on mac
# define HEX_ORANGEY	0xED840CFF //between orange and yellow on mac
# define HEX_PURPLE		0x800080FF //weak on MAC
# define HEX_OLILAS		0xA27CF1FF //blueish purple on mac
# define HEX_PINK		0xFFC0CBFF //pale pink on mac
# define HEX_BROWN		0x663300FF //weak dark orange on mac
# define HEX_OLIVE      0x808000FF
// 
# define HEX_GROUND		0x8E8849FF
# define HEX_SKY		0x6DC0C3FF
// define other default colors (minimap)

// pixel_utils.c
int		combine_rgba(int r, int g, int b, int a);
int		get_red(int color);
int		get_green(int color);
int		get_blue(int color);
int		get_alpha(int color);

// pixels.c
void	draw_pixel(mlx_image_t *img, int x, int y, int color);
int		get_pixel(mlx_image_t *img, int x, int y);

#endif // PIXELS_H
