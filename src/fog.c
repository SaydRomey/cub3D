/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:56:13 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/16 01:15:50 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	normalize_fog(float distance, float min, float max)
{
	float	clamped_dist;
	float	normalized_dist;

	clamped_dist = ft_fclamp(distance, min, max);

	// normalize the distance to a [0, 1] range, based on bounds
	normalized_dist = (clamped_dist - min) / (max - min);
	
	return (normalized_dist);
}

int	lerp_color(int color1, int color2, float fraction)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = (int)ft_lerp(get_red(color1), get_red(color2), fraction);
	green = (int)ft_lerp(get_green(color1), get_green(color2), fraction);
	blue = (int)ft_lerp(get_blue(color1), get_blue(color2), fraction);
	alpha = (int)ft_lerp(get_alpha(color1), get_alpha(color2), fraction);

	return (combine_rgba(red, green, blue, alpha));
}

int	fog_effect(int color, float raw_dist, float min, float max, int fog_color)
{
	float	dist;

	dist = normalize_fog(raw_dist, min, max);
	return (lerp_color(color, fog_color, dist));
}

/* ************************************************************************** */

static float	normalize_shadow(float distance, float min, float max)
{
	float	clamped_dist;
	float	normalized_dist;

	clamped_dist = ft_fclamp(distance, min, max);

	// normalize the distance to a [0, 1] range, based on bounds
	normalized_dist = (clamped_dist - min) / (max - min);

	// invert normalized for shadow calculation
	return (1.0f - normalized_dist);
}

int	shadow_effect(int color, float raw_dist, float min, float max)
{
	int		red;
	int		green;
	int		blue;
	int		alpha;
	float	dist;
	
	dist = normalize_shadow(raw_dist, min, max);

	red = (color >> 24) & 0xFF;
	green = (color >> 16) & 0xFF;
	blue = (color >> 8) & 0xFF;
	alpha = color & 0xFF;

	red = (int)(red * dist);
	green = (int)(green * dist);
	blue = (int)(blue * dist);
	
	// red = (get_red(color) * dist);
	// green = (get_green(color) * dist);
	// blue = (get_blue(color) * dist);
	// alpha = get_alpha(color);
	
	return (combine_rgba(red, green, blue, alpha));
}

/*
Distance based fog

modify the _color of the pixels based on their distance from the camera/viewpoint
the further away an object is, the more it blends with the fog _color

- calculate distance between camera and pixel being rendered,
use this distance to compute blend factor between pixel's original _color and fog's _color
the further away a pixel is, the closer it is to the fog _color
*/

/*
Exponential fog

calculate the blend factor using an exponential function of the distance.
This creates a denser fog effect as the distance increases,
which can appear more realistic.

Similar to distance-based fog,
but we use an exponential function to calculate the blend factor.
Adjust the density parameter to control how quickly the fog effect increases with distance.
*/
// void	fog_test(void)
// {
// 	float	fog_factor = ft_exp(-distance * fog_density);
// 	fog_factor = ft_fclamp(fog_factor, 0.0, 1.0);
// }


/*
Using a fog layer?

*/