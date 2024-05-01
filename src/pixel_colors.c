/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:05:30 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/01 18:04:48 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	average_img_color(mlx_image_t *img)
{
	int	totals[4] = {0, 0, 0, 0};
	int	averages[4];
	int	count;

	count = 0;
	process_pixels(img, totals, &count);
	compute_averages(totals, count, averages);
	return (combine_rgba(averages[R], averages[G], averages[B], averages[A]));
}

int	average_color(int *colors, int n)
{
	int	totals[4] = {0, 0, 0, 0};
	int	averages[4];
	int	i;
	
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
