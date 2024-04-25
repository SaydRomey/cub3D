/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:33:47 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/24 14:17:03 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	// return (r << 24 | g << 16 | b << 8 | a);
*/
int	combine_rgba(int r, int g, int b, int a)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = r << 24;
	green = g << 16;
	blue = b << 8;
	alpha = a;
	return (red | green | blue | alpha);
}

int	get_red(int color)
{
	return ((color >> 24) & 0xFF);
}

int	get_green(int color)
{
	return ((color >> 16) & 0xFF);
}

int	get_blue(int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_alpha(int color)
{
	return (color & 0xFF);
}
