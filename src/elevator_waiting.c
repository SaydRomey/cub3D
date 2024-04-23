/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevator_waiting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:54:32 by oroy              #+#    #+#             */
/*   Updated: 2024/04/22 13:06:27 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	elevator_waiting(void)
{
	double	start_time;
	double	elapsed_time;
	int		wait_time;

	wait_time = 1;
	start_time = mlx_get_time();
	elapsed_time = start_time;
	while (elapsed_time < start_time + wait_time)
		elapsed_time = mlx_get_time();
}
