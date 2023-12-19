/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:48:59 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/19 13:06:16 by cdumais          ###   ########.fr       */
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

/*
returns true if the 'to_verify' point is within the area of 'origin' to 'end'
*/
int	is_in_the_zone(t_point to_verify, t_point origin, t_point end)
{
	if (to_verify.x >= origin.x && to_verify.x <= end.x && \
		to_verify.y >= origin.y && to_verify.y <= end.y)
		return (TRUE);
	return (FALSE);
}

int	is_in_window(t_point to_verify)
{
	if (to_verify.x > 0 && to_verify.x < WIDTH && \
		to_verify.y > 0 && to_verify.y < HEIGHT)
		return (TRUE);
	return (FALSE);
}
