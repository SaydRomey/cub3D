/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:13:16 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/15 20:28:39 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_cub *cub)
{
	clear_image(&(cub->img));

	draw_mini_map(&(cub->img), &(cub->map));
	draw_player(&(cub->img), &(cub->player));
	
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img_ptr, 0, 0);
}
