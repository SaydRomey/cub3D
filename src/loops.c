/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:57:25 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/17 15:58:02 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// void	tmp_change_lvl_hook(t_cub *cub)
// {
// 	if (cub->keys.one)
// 		change_level(1);
// 	else
// 		change_level(0);
// }

static void	update_controls(t_cub *cub)
{
	t_level	*lvl;

	lvl = get_level(cub->current_level);
	if (lvl)
		lvl->mini.img->instances->enabled = cub->keys.m;
	
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
	
	update_player(cub); //movement based on keyhooks
	
	elevator_events(cub); //animation and level change trigger

	//// level change	
	
	// if (level chosen != cub->current_level)
	// 	change_level(level chosen);
	// tmp_change_lvl_hook(cub);

	// update_vfx(&cub->vfx);

	lvl = get_level(cub->current_level);
	if (lvl)
	{
		draw_radar(&lvl->mini);
		// draw_radar(&lvl->mini, &lvl->map, &cub->player);
	}
	
	// draw_assets()?

	raycast(cub);
}



