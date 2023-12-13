/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:48:59 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/13 15:01:19 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mlx_text(t_cub *mlx, char *str, int x, int y)
{
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, x, y, TEXT_COLOR, str);
	return (0);
}

void	proof(char *msg)
{
	ft_printf("%s\n", msg);
}

// void	toggle(int *toggle)
// {
// 	if (*toggle == ON)
// 		*toggle = OFF;
// 	else
// 		*toggle = ON;
// }
