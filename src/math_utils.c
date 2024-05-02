/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:11:42 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/02 01:19:54 by cdumais          ###   ########.fr       */
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

/*
'a' start value
'b' end value
't' interpolation factor that ranges from 0 to 1

((1 - t) * a + t * b)
*/
float	ft_lerp(float a, float b, float t)
{
	return (a + (b - a) * t);
}

/* ************************************************************************** */

/*
returns the euclidian distance between two points

(sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
*/
float	magnitude_between(t_fpoint a, t_fpoint b)
{
	t_fpoint	delta;
	float		distance;

	delta.x = b.x - a.x;
	delta.y = b.y - a.y;
	distance = sqrt(delta.x * delta.x + delta.y * delta.y);
	return (distance);
}

/*
*/
t_fpoint	rotate_vector(t_fpoint vector, float angle)
{
	t_fpoint	rotated;

	rotated.x = vector.x * cos(angle) - vector.y * sin(angle);
	rotated.y = vector.x * sin(angle) + vector.y * cos(angle);
	return (rotated);
}
