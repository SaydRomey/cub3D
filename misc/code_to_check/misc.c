/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:20:47 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/13 15:21:01 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
