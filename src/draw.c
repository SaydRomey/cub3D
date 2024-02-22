/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:07:33 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/22 13:49:57 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(mlx_image_t *img, t_point start, t_point end, int color)
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

void	draw_rectangle(mlx_image_t *img, t_point origin, t_point end, int color)
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

void	draw_ceiling(mlx_image_t *img, int color)
{
	t_point	start;
	t_point	end;
	
	start.x = 0;
	start.y = 0;
	end.x = img->width;
	end.y = img->height / 2;
	draw_rectangle(img, start, end, color);
}
void	draw_floor(mlx_image_t *img, int color)
{
	t_point	start;
	t_point	end;
	
	start.x = 0;
	start.y = img->height / 2;
	end.x = img->width;
	end.y = img->height;
	draw_rectangle(img, start, end, color);
}

void	draw_background(mlx_image_t *img, int color)
{
	t_point	dimensions;
	
	dimensions.x = img->width;
	dimensions.y = img->height;
	draw_rectangle(img, (t_point){0, 0}, dimensions, color);
}

/* ************************************************************************** */

void	draw_circle(mlx_image_t *img, t_point origin, int radius, int color)
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

void	draw_triangle(mlx_image_t *img, t_point p1, t_point p2, t_point p3, int color)
{
	draw_line(img, p1, p2, color);
	draw_line(img, p2, p3, color);
	draw_line(img, p3, p1, color);
}

// void	draw_circle_hollow(mlx_image_t *img, t_point origin, int radius, int thickness, int color)
// {
// 	int	i;
// 	int	j;
// 	int	distance_squared;
// 	int	radius_squared;
// 	int	inner_radius_squared;

// 	radius_squared = radius * radius;
// 	inner_radius_squared = (radius - thickness) * (radius - thickness);
// 	i = 0;
// 	while (i < radius * 2)
// 	{
// 		j = 0;
// 		while (j < radius * 2)
// 		{
// 			distance_squared = (i - radius) * (i - radius) + (j - radius) * (j
// 					- radius);
// 			if (distance_squared < radius_squared
// 				&& distance_squared > inner_radius_squared)
// 				draw_pixel(img, origin.x - radius + j, origin.y - radius + i,
// 						color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

/*
function to test colors
*/
// void	test_line(t_cub cub)
// {
// 	int	color = HEX_PURPLE;
// 	int	color_compare = HEX_MAGENTA;
// 	int	mini_color = color;
// 	int	mini_compare = color_compare;

// 	draw_line(cub.img, (t_point){0, 0}, (t_point){WIDTH, HEIGHT}, color); //diagonal
// 	draw_line(cub.img, (t_point){10, 0}, (t_point){WIDTH + 10, HEIGHT - 10}, color_compare); //diagonal
// 	draw_line(cub.img, (t_point){WIDTH / 2, 0}, (t_point){WIDTH / 2, HEIGHT}, color); //vertical
// 	draw_line(cub.img, (t_point){WIDTH / 2 + 10, 0}, (t_point){WIDTH / 2 + 10, HEIGHT}, color_compare); //vertical
// 	draw_line(cub.img, (t_point){0, HEIGHT / 2}, (t_point){WIDTH, HEIGHT / 2}, color); //horizontal
// 	draw_line(cub.img, (t_point){0, HEIGHT / 2 + 10}, (t_point){WIDTH, HEIGHT / 2 + 10}, color_compare); //horizontal
// 	// 
// 	draw_line(cub.mini, (t_point){0, 0}, (t_point){cub.config.minimap_width, cub.config.minimap_height}, mini_color); //diagonal
// 	draw_line(cub.mini, (t_point){10, 0}, (t_point){cub.config.minimap_width + 10, cub.config.minimap_height}, mini_compare); //diagonal
// 	draw_line(cub.mini, (t_point){cub.config.minimap_width / 2, 0}, (t_point){cub.config.minimap_width / 2, cub.config.minimap_height}, mini_color); //vertical
// 	draw_line(cub.mini, (t_point){cub.config.minimap_width / 2 + 10, 0}, (t_point){cub.config.minimap_width / 2 + 10, cub.config.minimap_height}, mini_compare); //vertical
// 	draw_line(cub.mini, (t_point){0, cub.config.minimap_height / 2}, (t_point){WIDTH, cub.config.minimap_height / 2}, mini_color); //horizontal
// 	draw_line(cub.mini, (t_point){0, cub.config.minimap_height / 2 + 10}, (t_point){WIDTH, cub.config.minimap_height / 2 + 10}, mini_compare); //horizontal
// }
