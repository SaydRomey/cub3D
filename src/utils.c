/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:39:37 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/10 16:20:02 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	toggle(bool *choice)
{
	if (*choice == ON)
		*choice = OFF;
	else
		*choice = ON;
}

void	change_window_title(char *filepath)
{
	char	*title;

	title = ft_strjoin("cub3D - ", filepath);
	mlx_set_window_title(call_cub()->mlx, title);
	free(title);
}
