/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:39:37 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/11 18:29:58 by cdumais          ###   ########.fr       */
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
			// check texture dimensions? is power of 2
			// if (map->wall_textures_img[i]->width % 2 == 0 && ..)
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
		return (0x000000FF); // color is already validated in parsing
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

/*
if 'x' or 'y' is negative, the image's 'x' or 'y' stays the same
*/
void	move_img(mlx_image_t *img, int x, int y)
{
	if (!img)
		return ;
	if (x > 0)
		img->instances->x = x;
	if (y > 0)
		img->instances->y = y;
}
