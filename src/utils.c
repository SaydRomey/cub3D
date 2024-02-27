/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:39:37 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/27 15:57:25 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_int(int r, int g, int b)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = r << 24;
	green = g << 16;
	blue = b << 8;
	alpha = 0xFF;
	return (red | green | blue | alpha);
}

static int	color_is_invalid(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (TRUE);
	return (FALSE);
}

int	get_color(t_scene *scene, int id)
{
	int	r;
	int	g;
	int	b;
	int	color_int;

	r = ft_atoi(scene->colors[id][R]);
	g = ft_atoi(scene->colors[id][G]);
	b = ft_atoi(scene->colors[id][B]);
	if (color_is_invalid(r, g, b))
	{
		// error: invalid color
		return (0x000000FF);
	}
	color_int = rgb_to_int(r, g, b);
	return (color_int);
}

/* ************************************************************************** */


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
