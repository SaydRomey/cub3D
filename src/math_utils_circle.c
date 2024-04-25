/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils_circle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:29:46 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/22 20:04:49 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
bool	is_in_annulus(t_fpoint point, t_fpoint center, \
int outer_radius, int inner_radius)
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
	return (distance_squared < outer_radius_squared \
	&& distance_squared > inner_radius_squared);
}
