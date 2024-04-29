/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __unused.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:56:11 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/29 15:15:23 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
void	add_segworld(t_list **levels)
{
	t_level	*seg_lvl;
	t_list	*node;

	seg_lvl = (t_level *)ft_calloc(1, sizeof(t_level));
	if (seg_lvl)
	{
		// seg_lvl->...
	}
	else
		set_error("Malloc error");
	if (!there_is_a_problem())
	{
		node = ft_lstnew(seg_lvl);
		if (!node)
		{
			delete_level(seg_lvl);
			set_error("Malloc error");
		}
		else
			ft_lstadd_back(levels, node);
	}
	else
		error();
}
*/

/*
check if we can modify this to take a real color instead of a grayscale ..

*/
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
in case the dst image is smaller
*/
static int	pixel_is_valid(mlx_image_t *img, t_u32 x, t_u32 y)
{
	return (x < img->width && y < img->height);
}

/*
copy an image to another image
*/
void	put_img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)src->width)
	{
		j = 0;
		while (j < (int)src->height)
		{
			if (pixel_is_valid(src, i, j))
				draw_pixel(dst, x + i, y + j, get_pixel(src, i, j));
			j++;
		}
		i++;
	}
}

/* ************************************************************************** */
void	draw_background(mlx_image_t *img, int color)
{
	t_fpoint	dimensions;

	dimensions.x = img->width;
	dimensions.y = img->height;
	draw_rectangle(img, (t_fpoint){0, 0}, dimensions, color);
}

// void	draw_triangle(mlx_image_t *img, t_triangle *triangle, int color)
// {
// 	t_fpoint	front;
// 	t_fpoint	left;
// 	t_fpoint	right;

// 	front = triangle->front;
// 	left = triangle->left;
// 	right = triangle->right;
// 	draw_line(img, left, front, color);
// 	draw_line(img, front, right, color);
// 	draw_line(img, right, left, color);
// }

/* ************************************************************************** */
int	n_in_array(int **array, int width, int height, int value_to_find)
{
	int	y;
	int	x;
	int	count;
	
	count = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (array[y][x] == value_to_find)
			{
				count++;
			}
			x++;
		}
		y++;
	}
	return (count);
}
/* ************************************************************************** */

