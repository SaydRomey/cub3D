/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:56:13 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/10 15:46:55 by cdumais          ###   ########.fr       */
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

/* ************************************************************************** */
int	apply_shadow(int color, float shadow_factor)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	shadow_factor = ft_fclamp(shadow_factor, 0.0f, 1.0f);
	red = (int)(get_red(color) * (1 - shadow_factor));
	green = (int)(get_green(color) * (1 - shadow_factor));
	blue = (int)(get_blue(color) * (1 - shadow_factor));
	alpha = get_alpha(color);

	return (combine_rgba(red, green, blue, alpha));
}

int	apply_bright(int color, float bright_factor)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	bright_factor = ft_fclamp(bright_factor, 0.0f, 1.0f);
	red = (int)get_red(color) + (int)((255 - get_red(color)) * bright_factor);
	green = (int)get_green(color) + (int)((255 - get_green(color)) * bright_factor);
	blue = (int)get_blue(color) + (int)((255 - get_blue(color)) * bright_factor);
	alpha = get_alpha(color);

	red = ft_clamp(red, 0, 255);
	green = ft_clamp(green, 0, 255);
	blue = ft_clamp(blue, 0, 255);

	return (combine_rgba(red, green, blue, alpha));
}
