/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:35:30 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/15 20:39:24 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(t_img *img)
{
	int	total_pixels;

	total_pixels = WIDTH * HEIGHT * PIXEL_SIZE;
	ft_bzero(img->addr, total_pixels);
}

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*image_data;
	int		pixel_index;
	int		byte_offset;
	int		*pixel_location;

	image_data = img->addr;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel_index = (x + y * WIDTH);
		byte_offset = pixel_index * PIXEL_SIZE;
		pixel_location = (int *)(image_data + byte_offset);
		*pixel_location = color;
	}
}

void	draw_line(t_img *img, t_point start, t_point end, int color)
{
	t_point	step;
	int		max;

	step.x = end.x - start.x;
	step.y = end.y - start.y;
	max = ft_max(ft_abs(step.x), ft_abs(step.y));
	step.x /= max;
	step.y /= max;
	while ((int)(start.x - end.x) || (int)(start.y - end.y))
	{
		draw_pixel(img, start.x, start.y, color);
		start.x += step.x;
		start.y += step.y;
	}
}

void	draw_rectangle(t_img *img, t_point origin, t_point end, int color)
{
	int x;
	int y;

	y = origin.y;
	// while (y < origin.y + end.y)
	while (y < end.y)
	{
		x = origin.x;
		// while (x < origin.x + end.x)
		while (x < end.x)
		{
			draw_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_img *img, t_player *player)
{
	t_point	size;

	size.x = player->position.x + player->size;
	size.y = player->position.y + player->size;

	// draw_pixel(img, x, y, player->color);
	// draw_line(img, player->position, size, player->color);
	draw_rectangle(img, player->position, size, player->color);
}
