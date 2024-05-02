/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:18:05 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/01 15:42:35 by oroy             ###   ########.fr       */
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

mlx_image_t	*copy_img(mlx_image_t *src, mlx_t *mlx)
{
	mlx_image_t	*copy;

	if (!src)
		return (NULL);
	copy = mlx_new_image(mlx, src->width, src->height);
	if (!copy)
		return (NULL);
	ft_memcpy(copy->pixels, src->pixels, \
	src->width * src->height * sizeof(int));
	return (copy);
}

mlx_image_t	*load_png(char *filepath, mlx_t *mlx)
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

void	clear_img(mlx_image_t *img)
{
	int	total_pixels;

	total_pixels = img->width * img->height * PIXEL_SIZE;
	ft_bzero(img->pixels, total_pixels);
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
