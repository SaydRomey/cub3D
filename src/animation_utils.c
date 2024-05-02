/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:22:17 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/01 22:22:29 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_animation(t_animation *anim)
{
	int	i;

	i = 0;
	while (i < anim->last_frame)
	{
		if (anim->frames[i])
		{
			mlx_delete_image(call_cub()->mlx, anim->frames[i]);
		}
		i++;
	}
	free(anim->frames);
}
