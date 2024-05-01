/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:05:30 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/30 21:34:22 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_color_totals(int *totals, int color)
{
	totals[R] += get_red(color);
	totals[G] += get_green(color);
	totals[B] += get_blue(color);
	totals[A] += get_alpha(color);
}

static void	process_pixels(mlx_image_t *img, int *totals, int *count)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < (int)img->height)
	{
		x = 0;
		while (x < (int)img->width)
		{
			color = get_pixel(img, x, y);
			add_color_totals(totals, color);
			(*count)++;
			x++;
		}
		y++;
	}
}

static void	compute_averages(int *totals, int count, int *averages)
{
	averages[R] = totals[R] / count;
	averages[G] = totals[G] / count;
	averages[B] = totals[B] / count;
	averages[A] = totals[A] / count;
}

int	average_color(mlx_image_t *img)
{
	int	totals[4] = {0, 0, 0, 0};
	int	count;
	int	averages[4];

	count = 0;
	process_pixels(img, totals, &count);
	compute_averages(totals, count, averages);
	return (combine_rgba(averages[0], averages[1], averages[2], averages[3]));
}

/* ************************************************************************** */

int	complement_color(int color)
{
	int	comp_red;
	int	comp_blue;
	int	comp_green;
	int	alpha;

	comp_red = 255 - get_red(color);
	comp_green = 255 - get_green(color);
	comp_blue = 255 - get_blue(color);
	alpha = get_alpha(color);
	return (combine_rgba(comp_red, comp_green, comp_blue, alpha));
}
