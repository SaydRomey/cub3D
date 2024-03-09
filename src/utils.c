/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:39:37 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/09 09:35:55 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*new_img(mlx_t *mlx, t_u32 width, t_u32 height, bool visible)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, width, height);
	if (!img)
		error_mlx();
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		error_mlx();
	img->instances->enabled = visible;
	return (img);
}

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
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		error_mlx();
	img->instances->enabled = false;
	mlx_delete_texture(texture);
	return (img);
}

void	extract_wall_textures(t_scene *scene, t_map *map, mlx_t *mlx)
{
	int	i;

	i = 0;
	while (i < WALL_TEXTURE_LEN)
	{
		if (scene->wall_textures[i])
		{
			map->wall_textures_img[i] = load_png(scene->wall_textures[i], mlx);
		}
		else
			map->wall_textures_img[i] = NULL;
		i++;
	}
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
		return (0x000000FF); //do we keep this ? color is already validated in parsing
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

void	fill_img(mlx_image_t *img, unsigned int grayscale)
{
	int	total_pixels;
	int	color;

	color = grayscale;
	if (grayscale > 255)
		color = 0;
	total_pixels = img->width * img->height * PIXEL_SIZE;
	ft_memset(img->pixels, color, total_pixels);
}

/* ************************************************************************** */

/*
returns true if the 'to_verify' point is within the area of 'origin' to 'end'

int	is_in_the_zone(t_fpoint to_verify, t_fpoint origin, t_fpoint end)
{
	if (to_verify.x >= origin.x && to_verify.x <= end.x && \
		to_verify.y >= origin.y && to_verify.y <= end.y)
		return (TRUE);
	return (FALSE);
}
*/
/*
// int	is_in_window(t_fpoint to_verify)
{
	if (to_verify.x > 0 && to_verify.x < WIDTH && \
		to_verify.y > 0 && to_verify.y < HEIGHT)
		return (TRUE);
	return (FALSE);
}
*/
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
