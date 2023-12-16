/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:14:26 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/15 17:21:05 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_test(t_img *img)
{
	t_point	start = {200, 200};
	t_point	end = {400, 400};

	draw_line(img, start, end, HEX_ORANGE);
	
	draw_pixel(img, 50, 50, HEX_GREEN);

	// t_point	rec_origin = {50, 50};
	// t_point	rec_end = {55, 80};

	// draw_rectangle(img, rec_origin, rec_end, HEX_PINK);
	
}
