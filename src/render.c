/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:13:16 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/18 14:45:22 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	text_test(t_cub *cub)
{
	mlx_text(cub, "Testing", cub->cursor.x - 40, cub->cursor.y - 40);
	mlx_text(cub, "Testing", WIDTH / 2, HEIGHT - 40);
}

void	render(t_cub *cub)
{
	clear_image(&cub->img);

	draw_mini_map(&cub->img, &cub->map);
	draw_player(&cub->img, &cub->player);
	draw_cursor(&cub->img, cub);

	text_test(cub);
	
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img_ptr, 0, 0);
}
