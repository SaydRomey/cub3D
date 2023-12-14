/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_linux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:17:03 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/14 12:30:55 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
linux version
*/
// int	terminate_mlx(t_cub *cub)
// {
// 	proof("Terminating mlx");
// 	if (cub->img.img_ptr)
// 		mlx_destroy_image(cub->mlx_ptr, cub->img.img_ptr);
// 	if (cub->win_ptr)
// 		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
// 	mlx_destroy_display(cub->mlx_ptr);
// 	safe_free((void **)&cub->mlx_ptr);
// 	exit(SUCCESS);
// }
