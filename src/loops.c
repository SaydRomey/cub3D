/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:57:25 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/18 18:24:11 by cdumais          ###   ########.fr       */
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

	// update_vfx(&cub->vfx);

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
		draw_radar(&lvl->mini);
	}
	raycast(cub);
}
