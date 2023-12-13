/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:09:05 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/13 15:16:59 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_input(int key, t_cub *cub)
{
	ft_printf("key: %d\n", key);
	// ft_printf("key: %s\n", key_to_str(key)); //?
	// 
	if (key == ESC)
		terminate_mlx(cub);
	render(cub);
	return (0);
}
