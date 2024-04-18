/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:57:25 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/18 17:36:06 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_controls(t_cub *cub)
{
	t_level	*lvl;

	lvl = get_level(cub->current_level);
	if (lvl)
	{
		lvl->mini.img->instances->enabled = (cub->keys.leftcontrol);
	}
	cub->radar_img->instances->enabled = cub->keys.m;
	cub->vfx.shadow.enabled = cub->keys.one;
}

/*
to be called in mlx_loop_hook()
*/
void	update(void *ptr)
{
	t_cub	*cub;
	t_level	*lvl;

	cub = (t_cub *)ptr;
	update_controls(cub);
	update_player(cub);
	elevator_events(cub);
	lvl = get_level(cub->current_level);
	if (lvl)
	{
		// if (cub->current_level != cub->chosen_level)
			// ... (if we split radar caluculations and rendering)

		draw_radar(&lvl->mini);
	}
	// update_vfx(&cub->vfx);
	raycast(cub);
}



