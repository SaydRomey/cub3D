/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:24:13 by olivierroy        #+#    #+#             */
/*   Updated: 2024/04/23 21:25:58 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_base_colors(t_cub *cub)
{
	draw_ceiling(cub->img, get_map(cub->current_level)->ceiling_color);
	draw_floor(cub->img, get_map(cub->current_level)->floor_color);
}
