/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:56:13 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/29 15:10:53 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	// normalize the distance to a [0, 1] range, based on bounds
	// invert normalized for shadow calculation

*/
static float	normalize_shadow(float distance, float min, float max)
{
	float	clamped_dist;
	float	normalized_dist;

	clamped_dist = ft_fclamp(distance, min, max);
	normalized_dist = (clamped_dist - min) / (max - min);
	return (1.0f - normalized_dist);
}

/*
	red = (color >> 24) & 0xFF;
	green = (color >> 16) & 0xFF;
	blue = (color >> 8) & 0xFF;
	alpha = color & 0xFF;
	red = (int)(red * dist);
	green = (int)(green * dist);
	blue = (int)(blue * dist);
*/
int	shadow_effect(int color, float raw_dist, float min, float max)
{
	int		red;
	int		green;
	int		blue;
	int		alpha;
	float	dist;

	dist = normalize_shadow(raw_dist, min, max);
	red = (get_red(color) * dist);
	green = (get_green(color) * dist);
	blue = (get_blue(color) * dist);
	alpha = get_alpha(color);
	return (combine_rgba(red, green, blue, alpha));
}
