/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segworld_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:53:33 by oroy              #+#    #+#             */
/*   Updated: 2024/04/24 20:05:31 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	get_orientation_vector(int orientation)
{
	if (orientation == 90)
		return ((t_point){0, -1});
	if (orientation == 270)
		return ((t_point){0, 1});
	if (orientation == 0)
		return ((t_point){-1, 0});
	if (orientation == 180)
		return ((t_point){1, 0});
	return ((t_point){0, 0});
}
