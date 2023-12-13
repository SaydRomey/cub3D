/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:34:06 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/13 15:08:25 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
mac version
*/
int	terminate_mlx(t_cub *cub)
{
	proof("Terminating mlx");
	safe_free((void **)&cub->mlx_ptr);
	exit(SUCCESS);
}

/*
linux version (change to t_cub later)
*/
// int	terminate_mlx(t_mlx *mlx)
// {
// 	if (mlx->img.img_ptr)
// 		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
// 	if (mlx->win_ptr)
// 		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
// 	mlx_destroy_display(mlx->mlx_ptr);
// 	safe_free((void **)&mlx->mlx_ptr);
// 	exit(SUCCESS);
// }
