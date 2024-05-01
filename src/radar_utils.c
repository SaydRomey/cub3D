/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:32:23 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/01 18:28:45 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	radar_interference(mlx_image_t *img, t_fpoint origin, int radius)
{
	int			i;
	int			j;
	t_fpoint	current_point;
	t_fpoint	center;
	int			color;

	center.x = origin.x;
	center.y = origin.y;
	i = 0;
	while (i < radius * 2)
	{
		j = 0;
		while (j < radius * 2)
		{
			color = interference_pixel();
			current_point.x = origin.x - radius + j;
			current_point.y = origin.y - radius + i;
			if (is_in_circle(current_point, center, radius))
				draw_pixel(img, current_point.x, current_point.y, color);
			j++;
		}
		i++;
	}
}

void	draw_radar_frame(t_radar *radar)
{
	draw_circle_hollow(radar->img, \
	(t_circle){radar->center, radar->radius + 10, HEX_BLACK}, 20);
	draw_circle_hollow(radar->img, \
	(t_circle){radar->center, radar->radius + 5, RADAR_FRAME_COL}, 10);
}
