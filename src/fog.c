/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:56:13 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/18 18:31:20 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	normalize_fog(float distance, float min, float max)
{
	float	clamped_dist;
	float	normalized_dist;

	clamped_dist = ft_fclamp(distance, min, max);
	normalized_dist = (clamped_dist - min) / (max - min);
	return (normalized_dist);
}

int	lerp_color(int color1, int color2, float factor)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = (int)ft_lerp(get_red(color1), get_red(color2), factor);
	green = (int)ft_lerp(get_green(color1), get_green(color2), factor);
	blue = (int)ft_lerp(get_blue(color1), get_blue(color2), factor);
	alpha = (int)ft_lerp(get_alpha(color1), get_alpha(color2), factor);
	return (combine_rgba(red, green, blue, alpha));
}

int	fog_effect(int color, float raw_dist, float min, float max, int fog_color)
{
	float	dist;

	dist = normalize_fog(raw_dist, min, max);
	return (lerp_color(color, fog_color, dist));
}

/* ************************************************************************** */
static int	blend_colors(int color1, int color2, float factor)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	factor = ft_fclamp(factor, 0.0f, 1.0f);
	red = (int)ft_lerp(get_red(color1), get_red(color2), factor);
	green = (int)ft_lerp(get_green(color1), get_green(color2), factor);
	blue = (int)ft_lerp(get_blue(color1), get_blue(color2), factor);
	alpha = (int)get_alpha(color1);
	return (combine_rgba(red, green, blue, alpha));
}

int	fog_effect2(int color, float distance)
{
	t_fog	*fog;
	float	factor;

	fog = &call_cub()->vfx.fog;
	factor = distance / fog->max;
	factor = ft_fclamp(factor, 0.0f, 1.0f);
	return (blend_colors(color, fog->color, factor));
}

/* ************************************************************************** */
/* ************************************************************************** */

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
	// red = (get_red(color) * dist);
	// green = (get_green(color) * dist);
	// blue = (get_blue(color) * dist);
	// alpha = get_alpha(color);

*/
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
	return (combine_rgba(red, green, blue, alpha));
}
