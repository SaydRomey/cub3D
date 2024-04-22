/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:02:54 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/22 17:20:33 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
frees t_cub and mlx ressources


*/
void	cleanup(t_cub *cub)
{
	if (cub->levels)
	{
		ft_lstclear(&cub->levels, delete_level);
	}
	cleanup_elevator(&cub->elevator);
	mlx_delete_image(cub->mlx, cub->img);
	mlx_delete_image(cub->mlx, cub->radar_img);
	mlx_terminate(cub->mlx);
}
