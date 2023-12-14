/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:14:26 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/13 20:14:57 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_test(t_img *img)
{
	t_point	start = {200, 200};
	t_point	end = {400, 400};

	draw_line(img, start, end, HEX_ORANGE);
	
	draw_pixel(img, 50, 50, HEX_GREEN);
	draw_pixel(img, 150, 150, HEX_YELLOW);
	
}
