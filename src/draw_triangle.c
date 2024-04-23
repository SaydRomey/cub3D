/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:15:13 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/22 20:02:49 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	draw_triangle(mlx_image_t *img, t_triangle *tri, int color)
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

static t_fpoint	calculate_centroid(t_fpoint a, t_fpoint b, t_fpoint c)
{
	t_fpoint	centroid;

	centroid.x = (a.x + b.x + c.x) / 3;
	centroid.y = (a.y + b.y + c.y) / 3;
	return (centroid);
}

static t_fpoint	calculate_inner_vertex(t_fpoint outer, \
t_fpoint centroid, int thickness)
{
	t_fpoint	inner;
	float		ratio;

	ratio = (magnitude_between(outer, centroid) - thickness) \
	/ magnitude_between(outer, centroid);
	inner.x = centroid.x + ratio * (outer.x - centroid.x);
	inner.y = centroid.y + ratio * (outer.y - centroid.y);
	return (inner);
}

void	draw_triangle_hollow(mlx_image_t *img, t_triangle *tri, \
int thickness, int color)
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
			if (point_in_triangle(point, *tri) \
			&& !point_in_triangle(point, inner_tri))
				draw_pixel(img, point.x, point.y, color);
			point.x++;
		}
		point.y++;
	}
}
