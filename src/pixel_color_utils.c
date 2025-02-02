/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:24:07 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/02 17:12:25 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_color_totals(int *totals, int color)
{
	totals[R] += get_red(color);
	totals[G] += get_green(color);
	totals[B] += get_blue(color);
	totals[A] += get_alpha(color);
}

void	process_pixels(mlx_image_t *img, int *totals, int *count)
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

void	compute_averages(int *totals, int count, int *averages)
{
	averages[R] = totals[R] / count;
	averages[G] = totals[G] / count;
	averages[B] = totals[B] / count;
	averages[A] = totals[A] / count;
}

void	draw_opaque_pixel(mlx_image_t *img, int x, int y, int color)
{
	if (get_alpha(color) == 255)
		draw_pixel(img, x, y, color);
}

int	choose_pixel(int color, int default_color)
{
	if (get_alpha(color) != 255)
		return (default_color);
	return (color);
}
