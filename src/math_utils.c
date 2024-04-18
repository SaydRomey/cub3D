/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:11:42 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/18 15:57:11 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	degree_to_radian(int degree)
{
	return (degree * PI / 180.0);
}

int	fix_angle(int angle)
{
	return (ft_wrap(angle, 0, 360));
}

bool	is_in_circle(t_fpoint point, t_fpoint center, int radius)
{
	t_fpoint	distance;
	float		distance_squared;

	distance.x = point.x - center.x;
	distance.y = point.y - center.y;
	distance_squared = distance.x * distance.x + distance.y * distance.y;
	return (distance_squared <= radius * radius);
}

/*
checks if a point is within the annular region
(the region between two concentric circles, a ring)
*/
bool	is_in_annulus(t_fpoint point, t_fpoint center, int outer_radius, int inner_radius)
{
	int	dx;
	int	dy;
	int	distance_squared;
	int	outer_radius_squared;
	int	inner_radius_squared;

	dx = point.x - center.x;
	dy = point.y - center.y;
	distance_squared = dx * dx + dy * dy;
	outer_radius_squared = outer_radius * outer_radius;
	inner_radius_squared = inner_radius * inner_radius;

	return (distance_squared < outer_radius_squared && distance_squared > inner_radius_squared);
}

/*
'a' start value
'b' end value
't' interpolation factor that ranges from 0 to 1
*/
float	ft_lerp(float a, float b, float t)
{
	// return ((1 - t) * a + t * b);
	return (a + (b - a) * t);
}

/* ************************************************************************** */

/*
determines the orientation of a point relative to a line segment

'vector1' : from 'b' to 'point'
'vector2' : from 'b' to 'a'

returns:
	positive if 'point' is to the left of the line from 'a' to 'b'
	negative if 'point' is to the right of the line from 'a' to 'b'
	0 if 'point' is on the line
*/
static int	cross_product(t_fpoint point, t_fpoint a, t_fpoint b)
{
	t_fpoint	vector1;
	t_fpoint	vector2;
	float		cross_product;

	vector1.x = point.x - b.x;
	vector1.y = point.y - b.y;
	vector2.x = a.x - b.x;
	vector2.y = a.y - b.y;
	cross_product = (vector1.x * vector2.y) - (vector2.x * vector1.y);
	
	return (cross_product);
	// return ((point.x - b.x) * (a.y - b.y) - (a.x - b.x) * (point.y - b.y)); //if we wanted a one-liner...
}

int	point_in_triangle(t_fpoint point, t_triangle triangle)
{
	int	d1;
	int	d2;
	int	d3;
	int	has_neg;
	int	has_pos;

	d1 = cross_product(point, triangle.front, triangle.left);
	d2 = cross_product(point, triangle.left, triangle.right);
	d3 = cross_product(point, triangle.right, triangle.front);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return (!(has_neg && has_pos));
}

