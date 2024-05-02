/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:05:30 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/02 00:21:18 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	average_img_color(mlx_image_t *img)
{
	int	totals[4];
	int	averages[4];
	int	count;

	totals[R] = 0;
	totals[G] = 0;
	totals[B] = 0;
	totals[A] = 0;
	count = 0;
	process_pixels(img, totals, &count);
	compute_averages(totals, count, averages);
	return (combine_rgba(averages[R], averages[G], averages[B], averages[A]));
}

int	average_color(int *colors, int n)
{
	int	totals[4];
	int	averages[4];
	int	i;

	totals[R] = 0;
	totals[G] = 0;
	totals[B] = 0;
	totals[A] = 0;
	i = 0;
	while (i < n)
	{
		add_color_totals(totals, colors[i]);
		i++;
	}
	compute_averages(totals, n, averages);
	return (combine_rgba(averages[R], averages[G], averages[B], averages[A]));
}

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
