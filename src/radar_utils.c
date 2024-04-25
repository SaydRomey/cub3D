/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:32:23 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/25 17:34:34 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	player_is_in_elevator(t_player *player)
{
	t_level	*lvl;

	lvl = get_level(call_cub()->current_level);
	if (lvl)
	{
		if (lvl->elevator_position.x == (int)player->position.x && \
			lvl->elevator_position.y == (int)player->position.y)
			return (true);
	}
	return (false);
}

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
			// color = random_pixel(42);
			// color = random_pixel(142);
			current_point.x = origin.x - radius + j;
			current_point.y = origin.y - radius + i;
			if (is_in_circle(current_point, center, radius))
				draw_pixel(img, current_point.x, current_point.y, color);
			j++;
		}
		i++;
	}
}
