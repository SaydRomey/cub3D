/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:39:37 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/06 15:27:24 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t *load_png(char *filepath, mlx_t *mlx)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	texture = mlx_load_png(filepath);
	if (!texture)
		error_mlx();
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		error_mlx();
	mlx_delete_texture(texture);
	return (img);
}

/* ************************************************************************** */

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
		ft_printf("\033[91mInvalid color\033[0m\n");
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

/* ************************************************************************** */

/*
returns true if the 'to_verify' point is within the area of 'origin' to 'end'
*/
// int	is_in_the_zone(t_fpoint to_verify, t_fpoint origin, t_fpoint end)
// {
// 	if (to_verify.x >= origin.x && to_verify.x <= end.x && \
// 		to_verify.y >= origin.y && to_verify.y <= end.y)
// 		return (TRUE);
// 	return (FALSE);
// }

// int	is_in_window(t_fpoint to_verify)
// {
// 	if (to_verify.x > 0 && to_verify.x < WIDTH && \
// 		to_verify.y > 0 && to_verify.y < HEIGHT)
// 		return (TRUE);
// 	return (FALSE);
// }

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
