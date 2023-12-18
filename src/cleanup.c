/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:25:19 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/17 19:15:17 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* this is temporary, not norminette approved !! */

#ifdef __linux__

/*
linux version
*/
int	terminate_mlx(t_cub *cub)
{
	proof("Terminating mlx");
	if (cub->img.img_ptr)
		mlx_destroy_image(cub->mlx_ptr, cub->img.img_ptr);
	if (cub->win_ptr)
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	mlx_destroy_display(cub->mlx_ptr);
	safe_free((void **)&cub->mlx_ptr);
	exit(SUCCESS);
}

#elif defined(__APPLE__) && defined(__MACH__)

/*
mac version
*/
int	terminate_mlx(t_cub *cub)
{
	proof("Terminating mlx");
	safe_free((void **)&cub->mlx_ptr);
	exit(SUCCESS);
}

#else
#error "Unsupported Operating System"
#endif
