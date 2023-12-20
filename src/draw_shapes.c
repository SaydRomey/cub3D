/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:11:52 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/20 12:36:19 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle(t_img *img, t_point origin, int radius, int color)
{
	int	i;
	int	j;
	int	distance_squared;
	int	radius_squared;

	radius_squared = radius * radius;
	i = 0;
	while (i < radius * 2)
	{
		j = 0;
		while (j < radius * 2)
		{
			// Calculate the distance from the center of the circle to the current pixel
			distance_squared = (i - radius) * (i - radius) + (j - radius) * (j
					- radius);
			// Check if the current pixel is within the circle's radius
			if (distance_squared < radius_squared)
				draw_pixel(img, origin.x - radius + j, origin.y - radius + i,
						color);
			j++;
		}
		i++;
	}
}

void	draw_circle_hollow(t_img *img, t_point origin, int radius,
		int thickness, int color)
{
	int	i;
	int	j;
	int	distance_squared;
	int	radius_squared;
	int	inner_radius_squared;

	radius_squared = radius * radius;
	inner_radius_squared = (radius - thickness) * (radius - thickness);
	i = 0;
	while (i < radius * 2)
	{
		j = 0;
		while (j < radius * 2)
		{
			distance_squared = (i - radius) * (i - radius) + (j - radius) * (j
					- radius);
			if (distance_squared < radius_squared
				&& distance_squared > inner_radius_squared)
				draw_pixel(img, origin.x - radius + j, origin.y - radius + i,
						color);
			j++;
		}
		i++;
	}
}

void	draw_tile(t_img *img, t_point origin, t_point size, int color)
{
	int	x;
	int	y;

	y = origin.y;
	while (y < origin.y + size.y)
	{
		x = origin.x;
		while (x < origin.x + size.x)
		{
			draw_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_triangle(t_img *img, t_point p1, t_point p2, t_point p3, int color)
{
	draw_line(img, p1, p2, color);
	draw_line(img, p2, p3, color);
	draw_line(img, p3, p1, color);
}

void	draw_rectangle(t_img *img, t_point origin, t_point end, int color)
{
	int	x;
	int	y;
	y = origin.y;
	while (y < origin.y + end.y)
	{
		x = origin.x;
		while (x < origin.x + end.x)
		{
			draw_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	color_background(t_img *img, t_map *map)
{
	t_point	start;
	t_point	end;

	// tmp
	draw_rectangle(img, (t_point){0, 0}, (t_point){WIDTH - 50, HEIGHT}, HEX_GRAY);
	// 

	start.x = WIDTH - 50;
	start.y = 0;
	end.x = WIDTH - 50;
	end.y = map->horizon.y;
	draw_rectangle(img, start, end, map->ceiling_color);

	start.x = WIDTH - 50;
	start.y = map->horizon.y;
	end.x = WIDTH - 50;
	end.y = HEIGHT;
	draw_rectangle(img, start, end, map->floor_color);
}
