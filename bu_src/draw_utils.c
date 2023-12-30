/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:35:30 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/20 12:18:31 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* bitshift version

int rgba_to_argb(int color)
{
	int	alpha;
	int	red;
	int	green;
	int	blue;

	alpha = (color & 0xFF000000) >> 24;
	red = (color & 0x00FF0000) >> 16;
	green = (color & 0x0000FF00) >> 8;
	blue = color & 0x000000FF;

	return (red << 24) | (green << 16) | (blue << 8) | alpha;
}
*/

/* explicative version

16777216	== 256^3 (for the alpha component)
65536		== 256^2 (for the red component)
256			== 256^1 (for the green component)
The blue component is already in the 256^0 place,
	so it doesn't need multiplication.

int rgba_to_argb(int color)
{
	int alpha = (color / 16777216) % 256;	// Extract the alpha component
	int red = (color / 65536) % 256;		// Extract the red component
	int green = (color / 256) % 256;		// Extract the green component
	int blue = color % 256;					// Extract the blue component

	return (red * 16777216 + green * 65536 + blue * 256 + alpha);
}
*/

/* hexa version

static int rgba_to_argb(int color)
{
	int	alpha;
	int	red;
	int	green;
	int	blue;

	alpha = (color / 0x1000000) % 0x100;
	red = (color / 0x10000) % 0x100;
	green = (color / 0x100) % 0x100;
	blue = color % 0x100;

	return (red * 0x1000000 + green * 0x10000 + blue * 0x100 + alpha);
}
*/

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*image_data;
	int		pixel_index;
	int		byte_offset;
	int		*pixel_location;

	image_data = img->addr;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel_index = (x + y * WIDTH);
		byte_offset = pixel_index * PIXEL_SIZE;
		pixel_location = (int *)(image_data + byte_offset);
		*pixel_location = color;
		// *pixel_location = rgba_to_argb(color);
	}
}

void	clear_image(t_img *img)
{
	int	total_pixels;

	total_pixels = WIDTH * HEIGHT * PIXEL_SIZE;
	ft_bzero(img->addr, total_pixels);
}

void	draw_line(t_img *img, t_point start, t_point end, int color)
{
	t_point	step;
	int		max;

	step.x = end.x - start.x;
	step.y = end.y - start.y;
	max = ft_max(ft_abs(step.x), ft_abs(step.y));
	step.x /= max;
	step.y /= max;
	while ((int)(start.x - end.x) || (int)(start.y - end.y))
	{
		draw_pixel(img, start.x, start.y, color);
		start.x += step.x;
		start.y += step.y;
	}
}
