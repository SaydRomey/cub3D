/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:36:14 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/14 19:45:25 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef enum e_effect_state
{
	NO_EFFECT,
	SHADOW_ONLY,
	FOG_ONLY,
	FLOOR_FOG
}	t_effect_state;

void	cycle_effect(t_vfx *vfx, bool key)
{
	static t_effect_state	current_effect = NO_EFFECT;
	static bool				last_key_state = false;

	if (key != last_key_state)
	{
		current_effect = (current_effect + 1) % 4;
		if (current_effect == NO_EFFECT)
		{
			proof("toggled to no effect");
			vfx->shadow_enabled = false;
			vfx->fog_enabled = false;
			vfx->floor_fog_enabled = false;
		}
		if (current_effect == SHADOW_ONLY)
		{
			proof("toggled to shadow effect");
			vfx->shadow_enabled = true;
			vfx->fog_enabled = false;
			vfx->floor_fog_enabled = false;
		}
		if (current_effect == FOG_ONLY)
		{
			proof("toggled to fog effect");
			vfx->shadow_enabled = false;
			vfx->fog_enabled = true;
			vfx->floor_fog_enabled = false;
		}
		if (current_effect == FLOOR_FOG)
		{
			proof("toggled to floor fog effect");
			vfx->shadow_enabled = false;
			vfx->fog_enabled = false;
			vfx->floor_fog_enabled = true;
		}
		last_key_state = key;
	}
}

/*
'1' toggles the textures
'2' cycles through examples of visual effects
*/
void	update_vfx(t_vfx *vfx)
{
	t_keys	keys;
	
	keys = call_cub()->keys;
	vfx->textures_enabled = !keys.one;
	cycle_effect(vfx, keys.two);

	if (vfx->floor_fog_enabled)
	{
		if (keys.leftcontrol && keys.up)
		{
			vfx->floor_fog_level -= 0.01f;
			if (vfx->floor_fog_level < 0)
				vfx->floor_fog_level = 0;
		}
		if (keys.leftcontrol && keys.down)
		{
			vfx->floor_fog_level += 0.01f;
			if (vfx->floor_fog_level > 1)
				vfx->floor_fog_level = 1;
		}
		ft_fclamp(vfx->floor_fog_level, 0.0f, 1.0f);
	}
}

void	wall_vfx(int *color, float distance, float tex_pos_y)
{
	int		modified_color;
	int		tmp_color;
	bool	side;
	t_vfx	*vfx;
	
	tmp_color = *color;
	modified_color = *color;
	side = call_cub()->raycast.side;
	vfx = &call_cub()->vfx;
	if (!vfx->textures_enabled)
	{
		if (side)
			tmp_color = (int)HEX_GRAY;
		else
			tmp_color = (int)HEX_DGRAY;
		modified_color = tmp_color;
	}
	if (vfx->shadow_enabled)
		modified_color = shadow_effect(tmp_color, distance, 0.0f, 5.0f);
	else if (vfx->fog_enabled)
		modified_color = fog_effect(tmp_color, distance, 0.0f, 5.0f, vfx->fog_color); //if hex_black, same as shadow..
	else if (vfx->floor_fog_enabled && tex_pos_y >= (TEX_HEIGHT * vfx->floor_fog_level))
		modified_color = fog_effect(tmp_color, distance, 1.0f, 5.0f, vfx->floor_fog_color);
	
	*color = modified_color;
}

// void	floor_ceiling_vfx(int *color[2], float distance) //missing info on what returns the distance..
// {
// 	t_vfx	*vfx;
// 	int		new_floor_color;
// 	int		new_ceiling_color;

// 	vfx = call_cub()->vfx;
// 	if (vfx->fog_enabled || vfx->floor_fog_enabled)
// 	{
// 		new_floor_color = fog_effect(*color[FLOOR], distance, vfx->floor_fog_color); //add fog level and the rest inside another function?
// 		if (vfx->fog_enabled)
// 			new_ceiling_color = fog_effect(*color[CEILING], distance, vfx->fog_color);
// 	}
// 	else if (vfx->shadow_enabled)
// 	{
// 		new_floor_color = shadow_effect();
// 		new_ceiling_color = shadow_effect();

// 		*color[FLOOR] = new_floor_color;
// 		*color[CEILING] = new_ceiling_color;
// 	}
// }
