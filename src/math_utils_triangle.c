/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils_triangle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:30:51 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/22 19:59:50 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
determines the orientation of a point relative to a line segment

'vector1' : from 'b' to 'point'
'vector2' : from 'b' to 'a'

returns:
	positive if 'point' is to the left of the line from 'a' to 'b'
	negative if 'point' is to the right of the line from 'a' to 'b'
	0 if 'point' is on the line
	
((point.x - b.x) * (a.y - b.y) - (a.x - b.x) * (point.y - b.y));
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
