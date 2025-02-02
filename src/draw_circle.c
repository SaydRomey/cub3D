/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:03:21 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/29 15:03:18 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle(mlx_image_t *img, t_circle circle)
{
	int			i;
	int			j;
	t_fpoint	pixel;
	t_fpoint	center;

	center.x = circle.origin.x;
	center.y = circle.origin.y;
	i = 0;
	while (i < circle.radius * 2)
	{
		j = 0;
		while (j < circle.radius * 2)
		{
			pixel.x = circle.origin.x - circle.radius + j;
			pixel.y = circle.origin.y - circle.radius + i;
			if (is_in_circle(pixel, center, circle.radius))
				draw_pixel(img, pixel.x, pixel.y, circle.color);
			j++;
		}
		i++;
	}
}

void	draw_circle_hollow(mlx_image_t *img, t_circle circle, int thickness)
{
	int			i;
	int			j;
	t_fpoint	pixel;
	t_fpoint	center;
	int			inner_radius;

	center.x = circle.origin.x;
	center.y = circle.origin.y;
	inner_radius = circle.radius - thickness;
	i = 0;
	while (i < circle.radius * 2)
	{
		j = 0;
		while (j < circle.radius * 2)
		{
			pixel.x = circle.origin.x - circle.radius + j;
			pixel.y = circle.origin.y - circle.radius + i;
			if (is_in_annulus(pixel, center, circle.radius, inner_radius))
				draw_pixel(img, pixel.x, pixel.y, circle.color);
			j++;
		}
		i++;
	}
}
