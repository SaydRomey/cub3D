/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:56:13 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/13 12:24:11 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// utils functions for this:

float	ft_fclamp(float value, float min, float max);

/*
'a' start value
'b' end value
't' interpolation factor that ranges from 0 to 1*/
float	ft_lerp(float a, float b, float t)
{
	return ((1 - t) * a + t * b);
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

/*
Distance based fog

modify the _color of the pixels based on their distance from the camera/viewpoint
the further away an object is, the more it blends with the fog _color

- calculate distance between camera and pixel being rendered,
use this distance to compute blend factor between pixel's original _color and fog's _color
the further away a pixel is, the closer it is to the fog _color
*/
void	fog_test(void)
{
	float	fog_factor = (fog_end - distance) / (fog_end - fog_start);
	fog_factor = ft_fclamp(fog_factor, 0.0, 0.1); //fog factor must be within [0, 1]
	
	int	pixel__color = get_pixel(img, x, y);
	int	fog__color = FOG__cOLOR;
	
	int	final__color = ft_lerp(pixel__color, fog__color, fog_factor);
}

/*
Exponential fog

calculate the blend factor using an exponential function of the distance.
This creates a denser fog effect as the distance increases,
which can appear more realistic.

Similar to distance-based fog,
but we use an exponential function to calculate the blend factor.
Adjust the density parameter to control how quickly the fog effect increases with distance.
*/
void	fog_test(void)
{
	float	fog_factor = ft_exp(-distance * fog_density);
	fog_factor = ft_fclamp(fog_factor, 0.0, 1.0);
}


/*
Using a fog layer?

*/