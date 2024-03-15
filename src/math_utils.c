/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:11:42 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/14 04:35:57 by cdumais          ###   ########.fr       */
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

bool	is_in_circle(t_point point, t_point center, int radius)
{
	t_point	distance;
	int		distance_squared;

	distance.x = point.x - center.x;
	distance.y = point.y - center.y;
	distance_squared = distance.x * distance.x - distance.y * distance.y;
	return (distance_squared <= radius * radius);
	// return (pow(point.x - center.x, 2) + pow(point.y - center.y, 2)) <= pow(radius, 2);
}


/* ************************************************************************** */
// to put in libft ?

float	ft_fmax(float this, float that)
{
	if (this > that)
		return (this);
	else
		return (that);
}

float	ft_fmin(float this, float that)
{
	if (this < that)
		return (this);
	else
		return (that);
}

int	ft_clamp(int value, int min, int max)
{
	return (ft_max(ft_min(value, max), min));
}

float	ft_fclamp(float value, float min, float max)
{
	return (ft_fmax(ft_fmin(value, max), min));
}

float	ft_percentage(float value, float total)
{
	if (total == 0)
		return (0);
	return ((value / total) * 100);
}

/*
'a' start value
'b' end value
't' interpolation factor that ranges from 0 to 1*/
float	ft_lerp(float a, float b, float t)
{
	return ((1 - t) * a + t * b);
	// return (a + (b - a) * t);
}



/* example
t_rgb	start_color = {255, 0, 0}; //red
t_rgb	end_color = {0, 0, 255}; //blue
float	progress = 0.5; //halfway through the transition

t_rgb	current_color;
current_color.r = (int)ft_lerp(start_color.r, end_color.r, progress);
current_color.g = (int)ft_lerp(start_color.g, end_color.g, progress);
current_color.b = (int)ft_lerp(start_color.b, end_color.b, progress);
*/

/*
if we need to always return a positive remainder
*( % can return a negative?)
useful for array indices or circular buffers, to avoid an invalid negative index
*/
int	ft_mod(int a, int b)
{
	int	mod;
	
	mod = a % b;
	if (mod < 0)
		mod += b;
	return (mod);
}

/*
** less accurate than the real 'exp'
* modify 'n_terms' for accuracy vs performance (to test)
*/
float	ft_exp(float x)
{
	int			n;
	const int	n_terms = 20; //number of terms in Taylor series for the approximation
	float		sum = 1.0f; //start with the first term of the series
	float		term = 1.0f; //current term, starting with 1 (which is x^0/0!)

	n = 1;
	while (n <= n_terms)
	{
		term *= x / n; //calculate next term in the series
		sum += term; //add current term to the sum
		n++;
	}
	return (sum);
}

/* ************************************************************************** */

/*
float distance(ax,ay,bx,by,ang){ return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);}
*/
// float	distance(t_fpoint a, t_fpoint b, float angle)
// {
// 	float	rad_angle;
// 	float	delta_x;
// 	float	delta_y;

// 	rad_angle = degree_to_radian(angle);
// 	delta_x = b.x - a.x;
// 	delta_y = b.y - a.y;
// 	return (cos(rad_angle) * delta_x - sin(rad_angle) * delta_y);
// }
