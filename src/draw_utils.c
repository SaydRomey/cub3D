/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:35:30 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/17 19:41:42 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(t_img *img)
{
	int	total_pixels;

	total_pixels = WIDTH * HEIGHT * PIXEL_SIZE;
	ft_bzero(img->addr, total_pixels);
}

void	fill_image(t_img *img, int color)
{
	int	total_pixels;

	total_pixels = WIDTH * HEIGHT * PIXEL_SIZE;
	ft_bzero(img->addr, total_pixels);
	ft_memset(img->addr, color, total_pixels);

}

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*image_data;
	int		pixel_index;
	int		byte_offset;
	int		*pixel_location;

	image_data = img->addr;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel_index = (x + y * WIDTH);
		byte_offset = pixel_index * PIXEL_SIZE;
		pixel_location = (int *)(image_data + byte_offset);
		*pixel_location = color;
	}
}

void	draw_line(t_img *img, t_point start, t_point end, int color)
{
	t_point	step;
	int		max;

	step.x = end.x - start.x;
	step.y = end.y - start.y;
	max = ft_max(ft_abs(step.x), ft_abs(step.y));
	step.x /= max;
	step.y /= max;
	while ((int)(start.x - end.x) || (int)(start.y - end.y))
	{
		draw_pixel(img, start.x, start.y, color);
		start.x += step.x;
		start.y += step.y;
	}
}

// 

void	draw_rect(t_img *img, t_point origin, t_point size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size.y && i + origin.y < HEIGHT)
	{
		j = 0;
		while (j < size.x && j + origin.x < WIDTH)
		{
			draw_pixel(img, origin.x + j, origin.y + i, color);
			j++;
		}
		i++;
	}
}
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
