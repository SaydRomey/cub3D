/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:07:33 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/18 00:27:15 by cdumais          ###   ########.fr       */
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

// void	draw_full_triangle(mlx_image_t *img, t_triangle *tri, int color)
// {
// 	int			min_x;
// 	int			max_x;
// 	int			min_y;
// 	int			max_y;
// 	t_fpoint	point;

// 	min_x = ft_fmin(tri->left.x, ft_fmin(tri->right.x, tri->front.x));
// 	max_x = ft_fmax(tri->left.x, ft_fmax(tri->right.x, tri->front.x));
// 	min_y = ft_fmin(tri->left.y, ft_fmin(tri->right.y, tri->front.y));
// 	max_y = ft_fmax(tri->left.y, ft_fmax(tri->right.y, tri->front.y));

// 	point.y = min_y;
// 	while (point.y <= max_y)
// 	{
// 		point.x = min_x;
// 		while (point.x <= max_x)
// 		{
// 			if (point_in_triangle(point, *tri))
// 				draw_pixel(img, point.x, point.y, color);
// 			point.x++;
// 		}
// 		point.y++;
// 	}
// }

/*
define the smallest rectangle that fully contains the triangle
*/
static void	define_bounding_box(t_triangle *tri, t_fpoint *min, t_fpoint *max)
{
	min->x = ft_fmin(tri->left.x, ft_fmin(tri->right.x, tri->front.x));
	max->x = ft_fmax(tri->left.x, ft_fmax(tri->right.x, tri->front.x));
	min->y = ft_fmin(tri->left.y, ft_fmin(tri->right.y, tri->front.y));
	max->y = ft_fmax(tri->left.y, ft_fmax(tri->right.y, tri->front.y));
}

void	draw_full_triangle(mlx_image_t *img, t_triangle *tri, int color)
{
	t_fpoint	min;
	t_fpoint	max;
	t_fpoint	point;

	define_bounding_box(tri, &min, &max);
	point.y = min.y;
	while (point.y <= max.y)
	{
		point.x = min.x;
		while (point.x <= max.x)
		{
			if (point_in_triangle(point, *tri))
				draw_pixel(img, point.x, point.y, color);
			point.x++;
		}
		point.y++;
	}
}

/* ************************************************************************** */

/*
returns the euxlidian distance between two points
*/
float	magnitude_between(t_fpoint a, t_fpoint b)
{
	t_fpoint	delta;
	float		distance;

	delta.x = b.x - a.x;
	delta.y = b.y - a.y;
	distance = sqrt(delta.x * delta.x + delta.y * delta.y);

	return (distance);	
	// return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

static t_fpoint	calculate_centroid(t_fpoint a, t_fpoint b, t_fpoint c)
{
	t_fpoint	centroid;

	centroid.x = (a.x + b.x + c.x) / 3;
	centroid.y = (a.y + b.y + c.y) / 3;

	return (centroid);
}

static t_fpoint	calculate_inner_vertex(t_fpoint outer, t_fpoint centroid, int thickness)
{
	t_fpoint	inner;
	float		ratio;
	
	ratio = (magnitude_between(outer, centroid) - thickness) / magnitude_between(outer, centroid);
	inner.x = centroid.x + ratio * (outer.x - centroid.x);
	inner.y = centroid.y + ratio * (outer.y - centroid.y);
	
	return (inner);
}
void	draw_full_triangle_hollow(mlx_image_t *img, t_triangle *tri, int thickness, int color)
{
	t_fpoint	min;
	t_fpoint	max;
	t_fpoint	centroid;
	t_triangle	inner_tri;
	t_fpoint	point;

	define_bounding_box(tri, &min, &max);
	centroid = calculate_centroid(tri->left, tri->right, tri->front);
	inner_tri.left = calculate_inner_vertex(tri->left, centroid, thickness);
	inner_tri.right = calculate_inner_vertex(tri->right, centroid, thickness);
	inner_tri.front = calculate_inner_vertex(tri->front, centroid, thickness);
	
	point.y = min.y;
	while (point.y <= max.y)
	{
		point.x = min.x;
		while (point.x <= max.x)
		{
			if (point_in_triangle(point, *tri) && !point_in_triangle(point, inner_tri))
				draw_pixel(img, point.x, point.y, color);
			point.x++;
		}
		point.y++;
	}
}

/* ************************************************************************** */
/* ************************************************************************** */

void	draw_circle(mlx_image_t *img, t_fpoint origin, int radius, int color)
{
	int		i;
	int		j;
	t_point	current_point;
	t_point	center = {origin.x, origin.y};

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

void	draw_circle_hollow(mlx_image_t *img, t_fpoint origin, int radius, int thickness, int color)
{
	int			i;
	int			j;
	t_fpoint	current_point;
	t_fpoint	center = {origin.x, origin.y};
	int			inner_radius;

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
