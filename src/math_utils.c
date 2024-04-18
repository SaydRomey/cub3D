/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:11:42 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/17 19:47:15 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	degree_to_radian(int degree)
{
	return (degree * PI / 180.0);
}

// int	fix_angle(int angle)
// {
// 	return (ft_wrap(angle, 0, 360));
// }

int	fix_angle(int angle)
{
	if (angle > 359)
		angle -= 360;
	else if (angle < 0)
		angle += 360;
	return (angle);
}

bool	is_in_circle(t_point point, t_point center, int radius)
{
	t_point	distance;
	int		distance_squared;

	distance.x = point.x - center.x;
	distance.y = point.y - center.y;
	distance_squared = distance.x * distance.x + distance.y * distance.y;
	return (distance_squared <= radius * radius);
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

static int	fpoint_sign(t_fpoint p1, t_fpoint p2, t_fpoint p3)
{
    return ((p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y));
}

int	point_in_triangle(t_fpoint p, t_triangle triangle)
{
	int	d1;
	int	d2;
	int	d3;
    int	has_neg;
	int	has_pos;

    d1 = fpoint_sign(p, triangle.front, triangle.left);
    d2 = fpoint_sign(p, triangle.left, triangle.right);
    d3 = fpoint_sign(p, triangle.right, triangle.front);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

