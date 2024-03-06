/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:11:42 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/06 10:50:23 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	degree_to_radian(int degree)
{
	return (degree * PI / 180.0);
}

int	fix_angle(int angle)
{
	if (angle > 359)
		angle -= 360;
	else if (angle < 0)
		angle += 360;
	return (angle);
}

int	is_inside_circle(t_fpoint to_check, t_fpoint circle_center, int radius)
{
	t_fpoint	distance; // from to_check to the circle of the center
	int		distance_squared;

	distance.x = to_check.x - circle_center.x;
	distance.y = to_check.y - circle_center.y;
	distance_squared = distance.x * distance.x - distance.y * distance.y;

	return (distance_squared <= radius * radius);
}

/*
float distance(ax,ay,bx,by,ang){ return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);}
*/
float	distance(t_fpoint a, t_fpoint b, float angle)
{
	float	rad_angle;
	float	delta_x;
	float	delta_y;

	rad_angle = degree_to_radian(angle);
	delta_x = b.x - a.x;
	delta_y = b.y - a.y;
	return (cos(rad_angle) * delta_x - sin(rad_angle) * delta_y);
}
