/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:49:39 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/25 18:05:17 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
place the values of 'color' at the address 'pixel'
*/
static void	set_pixel(unsigned char *pixel, int color)
{
	*(pixel++) = (unsigned char)(color >> 24);
	*(pixel++) = (unsigned char)(color >> 16);
	*(pixel++) = (unsigned char)(color >> 8);
	*(pixel++) = (unsigned char)(color & 0xFF);
}

void	draw_pixel(mlx_image_t *img, int x, int y, int color)
{
	unsigned char	*pixel;

	if (img)
	{
		if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
		{
			pixel = &img->pixels[(y * img->width + x) * PIXEL_SIZE];
			set_pixel(pixel, color);
		}
	}
}

/* ************************************************************************** */

int	get_pixel(mlx_image_t *img, int x, int y)
{
	unsigned char	*pixel;

	if (x > (int)img->width || y > (int)img->height)
		return ((unsigned char)0xFF000000);
	pixel = img->pixels + (y * img->width + x) * PIXEL_SIZE;
	return (combine_rgba(*(pixel), *(pixel + 1), *(pixel + 2), *(pixel + 3)));
}

/* ************************************************************************** */

/*
returns a random color, 'brightness_level' caps at 255
*/
int	random_pixel(int brightness_level)
{
	int	r;
	int	g;
	int	b;
	int	a;

	brightness_level = ft_clamp(brightness_level, 0, 255);
	r = ft_rand(0, brightness_level);
	g = ft_rand(0, brightness_level);
	b = ft_rand(0, brightness_level);
	a = 0xFF;
	return (combine_rgba(r, g, b, a));
}

int	interference_pixel(void)
{
	int	color;

	color = HEX_GRAY;
	if (ft_rand(0, 10) % 2)
		color = HEX_DGRAY;
	return (color);
}
