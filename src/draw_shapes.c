/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:11:52 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/19 14:53:54 by cdumais          ###   ########.fr       */
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
			distance_squared = (i - radius) * (i - radius) + (j - radius) * (j - radius);

			// Check if the current pixel is within the circle's radius
			if (distance_squared < radius_squared)
				draw_pixel(img, origin.x - radius + j, origin.y - radius + i, color);
			j++;
		}
		i++;
	}
}

void draw_circle_hollow(t_img *img, t_point origin, int radius, int thickness, int color)
{
    int i;
    int j;
    int distance_squared;
    int radius_squared;
    int inner_radius_squared;

    radius_squared = radius * radius;
    inner_radius_squared = (radius - thickness) * (radius - thickness);

    i = 0;
    while (i < radius * 2)
	{
        j = 0;
        while (j < radius * 2)
		{
            distance_squared = (i - radius) * (i - radius) + (j - radius) * (j - radius);

            if (distance_squared < radius_squared && distance_squared > inner_radius_squared)
                draw_pixel(img, origin.x - radius + j, origin.y - radius + i, color);
            j++;
        }
        i++;
    }
}

void	draw_tile(t_img *img, t_point origin, t_point size, int color)
{
	int x;
	int y;

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

// void	draw_rect(t_img *img, t_point origin, t_point end, int color)

void	color_background(t_img *img, int floor_color, int ceiling_color)
{
	t_point	start;
	t_point	end;

	start.x = WIDTH - 50;
	start.y = 0;
	end.x = WIDTH - 50;
	end.y = HEIGHT / 2;
	// draw_rect(img, start, end, ceiling_color);
	draw_line(img, start, end, ceiling_color);

	start.x = WIDTH - 50;
	start.y = HEIGHT;
	end.x = WIDTH - 50;
	end.y = HEIGHT / 2;
	// draw_rect(img, start, end, floor_color);
	draw_line(img, start, end, floor_color);
}
