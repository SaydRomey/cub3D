/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:39:37 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/26 22:17:29 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_int(t_rgb color)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;
	int	combined_color;

	red = color.r << 24;
	green = color.g << 16;
	blue = color.b << 8;
	alpha = 0xFF;
	combined_color = red | green | blue | alpha;
	return (combined_color);
}

void	toggle(bool *choice)
{
	if (*choice == ON)
		*choice = OFF;
	else
		*choice = ON;
}

void	clear_img(mlx_image_t *img)
{
	int	total_pixels;

	total_pixels = img->width * img->height * PIXEL_SIZE;
	ft_bzero(img->pixels, total_pixels);
}

/*
free everything from here
*/
void	cleanup(t_cub *cub)
{
	mlx_delete_image(cub->mlx, cub->img);
	mlx_delete_image(cub->mlx, cub->minimap_img);
	mlx_terminate(cub->mlx);
}

/* ************************************************************************** */

/*
returns true if the 'to_verify' point is within the area of 'origin' to 'end'
*/
int	is_in_the_zone(t_point to_verify, t_point origin, t_point end)
{
	if (to_verify.x >= origin.x && to_verify.x <= end.x && \
		to_verify.y >= origin.y && to_verify.y <= end.y)
		return (TRUE);
	return (FALSE);
}

int	is_in_window(t_point to_verify)
{
	if (to_verify.x > 0 && to_verify.x < WIDTH && \
		to_verify.y > 0 && to_verify.y < HEIGHT)
		return (TRUE);
	return (FALSE);
}

/*
to prevent accidents..
[...]
if (button == SCROLL_UP)
		cub->player.speed += 0.5;
	if (button == SCROLL_DOWN)
		cub->player.speed -= 0.5;
	cub->player.speed = speed_limit(cub->player.speed, SPEED_LIMIT);
[...]
*/
// static float	speed_limit(float speed, float limit)
// {
// 	if (speed >= limit)
// 		return (limit);
// 	if (speed <= 0)
// 		return (0);
// 	return (speed);
// }
