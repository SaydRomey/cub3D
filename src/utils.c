/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:48:59 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/18 15:16:23 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mlx_text(t_cub *mlx, char *str, int x, int y)
{
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, x, y, HEX_WHITE, str);
	return (0);
}

void	proof(char *msg)
{
	ft_printf("%s\n", msg);
}

void	toggle(int *toggle)
{
	if (*toggle == ON)
		*toggle = OFF;
	else
		*toggle = ON;
}

int	spawning_orientation(char direction)
{
	if (direction == 'N')
		return (90);
	if (direction == 'S')
		return (270);
	if (direction == 'E')
		return (0);
	if (direction == 'W')
		return (180);
	return (-1);
}
