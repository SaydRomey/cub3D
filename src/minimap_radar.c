/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_radar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:03:48 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/15 16:09:51 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	draw_radar(t_cub *cub)
{
	// t_fpoint	player_pos;
	
	t_point	center = {cub->radar_img->width / 2, cub->radar_img->height / 2};
	int		radius = 50; //test
	
	int	y;
	int	x;
	
	// player_pos = cub->player.position;
		
	// clear_img(cub->radar_img);
	draw_background(cub->radar_img, HEX_BLACK);

	y = 0;
	while (y < (int)cub->radar_img->height)
	{
		x = 0;
		while (x < (int)cub->radar_img->width)
		{
			if (is_in_circle((t_point){x, y}, center, radius))
			{
				draw_pixel(cub->radar_img, x, y, HEX_GRAY);
			}
			x++;
		}
		y++;
	}

	
}
