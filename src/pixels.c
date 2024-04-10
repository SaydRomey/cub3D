/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:49:39 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/10 16:08:44 by cdumais          ###   ########.fr       */
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
		if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
		{	
			pixel = &img->pixels[(y * img->width + x) * PIXEL_SIZE];
			set_pixel(pixel, color);
		}
}

/* ************************************************************************** */

int combine_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_pixel(mlx_image_t *img, int x, int y)
{
	unsigned char   *pixel;

	if (x > (int)img->width || y > (int)img->height)
		return ((unsigned char)0xFF000000);
	pixel = img->pixels + (y * img->width + x) * PIXEL_SIZE;
	return (combine_rgba(*(pixel), *(pixel + 1), *(pixel + 2), *(pixel + 3)));
}

/* ************************************************************************** */

int	get_red(int color)
{
	return ((color >> 24) & 0xFF);
}

int	get_green(int color)
{
	return ((color >> 16) & 0xFF);
}

int	get_blue(int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_alpha(int color)
{
	return (color & 0xFF);
}

/* ************************************************************************** */

int	rgb_to_int(int r, int g, int b)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = r << 24;
	green = g << 16;
	blue = b << 8;
	alpha = 0xFF;
	return (red | green | blue | alpha);
}

static int	color_is_invalid(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (TRUE);
	return (FALSE);
}

int	get_color(t_scene *scene, int id)
{
	int	r;
	int	g;
	int	b;
	int	color_int;

	r = ft_atoi(scene->colors[id][R]);
	g = ft_atoi(scene->colors[id][G]);
	b = ft_atoi(scene->colors[id][B]);
	if (color_is_invalid(r, g, b))
	{
		return (0x000000FF); // color is already validated in parsing
	}
	color_int = rgb_to_int(r, g, b);
	return (color_int);
}
