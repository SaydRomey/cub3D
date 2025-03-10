/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:54:12 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/02 11:48:31 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "utils.h"

# define PI			3.1415926535
# define ISO_ANGLE	0.523599

typedef struct s_circle
{
	t_fpoint	origin;
	int			radius;
	int			color;
}				t_circle;

typedef struct s_triangle
{
	float		half_base;
	float		height;
	t_point		centroid;
	t_fpoint	front;
	t_fpoint	left;
	t_fpoint	right;
	t_fpoint	base_center;
}				t_triangle;

// math_utils_circle.c
bool		is_in_circle(t_fpoint point, t_fpoint center, int radius);
bool		is_in_annulus(t_fpoint point, t_fpoint center, \
int outer_radius, int inner_radius);

// math_utils_triangle.c
int			point_in_triangle(t_fpoint p, t_triangle triangle);

// math_utils.c
float		degree_to_radian(int degree);
int			fix_angle(int angle);
float		ft_lerp(float a, float b, float t);
float		magnitude_between(t_fpoint a, t_fpoint b);
t_fpoint	rotate_vector(t_fpoint vector, float angle);

#endif // MATH_UTILS_H
