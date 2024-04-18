/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:07:33 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/17 19:45:25 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(mlx_image_t *img, t_fpoint start, t_fpoint end, int color)
{
	t_fpoint	step;
	int			max;

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

void	draw_rectangle(mlx_image_t *img, t_fpoint origin, t_fpoint end, int color)
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

void	draw_floor(mlx_image_t *img, int color)
{
	t_fpoint	start;
	t_fpoint	end;
	
	start.x = 0;
	start.y = img->height / 2;
	end.x = img->width;
	end.y = img->height;
	draw_rectangle(img, start, end, color);
}

void	draw_ceiling(mlx_image_t *img, int color)
{
	t_fpoint	start;
	t_fpoint	end;
	
	start.x = 0;
	start.y = 0;
	end.x = img->width;
	end.y = img->height / 2;
	draw_rectangle(img, start, end, color);
}

// a.k.a. fill_img ?
void	draw_background(mlx_image_t *img, int color)
{
	t_fpoint	dimensions;
	
	dimensions.x = img->width;
	dimensions.y = img->height;
	draw_rectangle(img, (t_fpoint){0, 0}, dimensions, color);
}

/* ************************************************************************** */

void	draw_triangle(mlx_image_t *img, t_triangle *triangle, int color)
{
	t_fpoint	front;
	t_fpoint	left;
	t_fpoint	right;

	front = triangle->front;
	left = triangle->left;
	right = triangle->right;
	draw_line(img, left, front, color);
	draw_line(img, front, right, color);
	draw_line(img, right, left, color);
}

void	draw_full_triangle(mlx_image_t *img, t_triangle *tri, int color)
{
	int			min_x;
	int			max_x;
	int			min_y;
	int			max_y;
    t_fpoint	p;

	min_x = ft_fmin(tri->left.x, ft_fmin(tri->right.x, tri->front.x));
    max_x = ft_fmax(tri->left.x, ft_fmax(tri->right.x, tri->front.x));
    min_y = ft_fmin(tri->left.y, ft_fmin(tri->right.y, tri->front.y));
    max_y = ft_fmax(tri->left.y, ft_fmax(tri->right.y, tri->front.y));

	p.y = min_y;
	while (p.y <= max_y)
	{
		p.x = min_x;
		while (p.x <= max_x)
		{
			if (point_in_triangle(p, *tri))
				draw_pixel(img, p.x, p.y, color);
			p.x++;
		}
		p.y++;
	}
}


void	draw_circle(mlx_image_t *img, t_fpoint origin, int radius, int color)
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
				draw_pixel(img, origin.x - radius + j, origin.y - radius + i,
						color);
			j++;
		}
		i++;
	}
}

void	draw_circle_hollow(mlx_image_t *img, t_fpoint origin, int radius, int thickness, int color)
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
