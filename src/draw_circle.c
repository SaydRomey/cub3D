/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:03:21 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/22 20:06:49 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle(mlx_image_t *img, t_fpoint origin, int radius, int color)
{
	int			i;
	int			j;
	t_fpoint	current_point;
	t_fpoint	center;

	center.x = origin.x;
	center.y = origin.y;
	i = 0;
	while (i < radius * 2)
	{
		j = 0;
		while (j < radius * 2)
		{
			current_point.x = origin.x - radius + j;
			current_point.y = origin.y - radius + i;
			if (is_in_circle(current_point, center, radius))
				draw_pixel(img, current_point.x, current_point.y, color);
			j++;
		}
		i++;
	}
}

void	draw_circle_hollow(mlx_image_t *img, t_fpoint origin, \
int radius, int thickness, int color)
{
	int			i;
	int			j;
	t_fpoint	current_point;
	t_fpoint	center;
	int			inner_radius;

	center.x = origin.x;
	center.y = origin.y;
	inner_radius = radius - thickness;
	i = 0;
	while (i < radius * 2)
	{
		j = 0;
		while (j < radius * 2)
		{
			current_point.x = origin.x - radius + j;
			current_point.y = origin.y - radius + i;
			if (is_in_annulus(current_point, center, radius, inner_radius))
				draw_pixel(img, current_point.x, current_point.y, color);
			j++;
		}
		i++;
	}
}
