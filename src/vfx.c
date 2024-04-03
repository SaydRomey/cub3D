// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   vfx.c                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/14 13:36:14 by cdumais           #+#    #+#             */
// /*   Updated: 2024/03/29 12:41:44 by oroy             ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3d.h"

// typedef enum e_effect_state
// {
// 	NO_EFFECT,
// 	SHADOW_ONLY,
// 	FOG_ONLY,
// 	FLOOR_FOG
// }	t_effect_state;

// void	cycle_effect(t_vfx *vfx, bool key)
// {
// 	static t_effect_state	current_effect = NO_EFFECT;
// 	static bool				last_key_state = false;

// 	if (key != last_key_state)
// 	{
// 		current_effect = (current_effect + 1) % 4;
// 		if (current_effect == NO_EFFECT)
// 		{
// 			proof("toggled to no effect");
// 			vfx->shadow_enabled = false;
// 			vfx->fog_enabled = false;
// 			vfx->floor_fog_enabled = false;
// 		}
// 		if (current_effect == SHADOW_ONLY)
// 		{
// 			proof("toggled to shadow effect");
// 			vfx->shadow_enabled = true;
// 			vfx->fog_enabled = false;
// 			vfx->floor_fog_enabled = false;
// 		}
// 		if (current_effect == FOG_ONLY)
// 		{
// 			proof("toggled to fog effect");
// 			vfx->shadow_enabled = false;
// 			vfx->fog_enabled = true;
// 			vfx->floor_fog_enabled = false;
// 		}
// 		if (current_effect == FLOOR_FOG)
// 		{
// 			proof("toggled to floor fog effect");
// 			vfx->shadow_enabled = false;
// 			vfx->fog_enabled = false;
// 			vfx->floor_fog_enabled = true;
// 		}
// 		last_key_state = key;
// 	}
// }

// /*
// '1' toggles the textures
// '2' cycles through examples of visual effects
// */
// void	update_vfx(t_vfx *vfx)
// {
// 	t_keys	keys;
	
// 	keys = call_cub()->keys;
// 	vfx->textures_enabled = !keys.one;
// 	cycle_effect(vfx, keys.two);

// 	if (vfx->floor_fog_enabled)
// 	{
// 		if (keys.leftcontrol && keys.up)
// 		{
// 			vfx->floor_fog_level -= 0.01f;
// 			if (vfx->floor_fog_level <= 0)
// 				vfx->floor_fog_level = 0;
// 			// printf("fog level: %f\n", vfx->floor_fog_level);
// 		}
// 		if (keys.leftcontrol && keys.down)
// 		{
// 			vfx->floor_fog_level += 0.01f;
// 			if (vfx->floor_fog_level >= 1)
// 				vfx->floor_fog_level = 1;
// 			// printf("fog level: %f\n", vfx->floor_fog_level);
// 		}
// 		ft_fclamp(vfx->floor_fog_level, 0.0f, 1.0f);
// 	}
// }

// void	wall_vfx(int *color, float distance, float tex_pos_y)
// {
// 	int		modified_color;
// 	int		tmp_color;
// 	bool	side;
// 	t_vfx	*vfx;

// 	(void)tex_pos_y; //tmp
	
// 	tmp_color = *color;
// 	modified_color = *color;
// 	side = call_cub()->raycast.ray.side;
// 	vfx = &call_cub()->vfx;
// 	if (!vfx->textures_enabled)
// 	{
// 		if (side)
// 			tmp_color = (int)HEX_GRAY;
// 		else
// 			tmp_color = (int)HEX_DGRAY;
// 		modified_color = tmp_color;
// 	}
// 	if (vfx->shadow_enabled)
// 		modified_color = shadow_effect(tmp_color, distance, 0.0f, 5.0f);
// 	else if (vfx->fog_enabled)
// 		modified_color = fog_effect(tmp_color, distance, 0.0f, 5.0f, vfx->fog_color); //if hex_black, same as shadow..
// 	else if (vfx->floor_fog_enabled)
// 	{
// 		modified_color = fog_effect(tmp_color, distance, 0.0f, (3.0f / (1.0f - vfx->floor_fog_level)), vfx->floor_fog_color);
		
// 		// if (tex_pos_y <= (TEX_HEIGHT * vfx->floor_fog_level))
// 			// modified_color = fog_effect(tmp_color, distance, 0.0f, (3.0f / (1.0 - vfx->floor_fog_level)), vfx->fog_color);
// 	}	
// 	*color = modified_color;
// }

// void	floor_ceiling_vfx(int *color[2], float distance)
// {
// 	t_vfx	*vfx;
// 	int		tmp_color[2];
// 	int		modified_color[2];
	
// 	tmp_color[FLOOR] = *color[FLOOR];
// 	tmp_color[CEILING] = *color[CEILING];
// 	modified_color[FLOOR] = *color[FLOOR];
// 	modified_color[CEILING] = *color[CEILING];
// 	vfx = &call_cub()->vfx;
// 	if (!vfx->textures_enabled) //maybe use a different flag specific for floor/ceiling
// 	{
// 		tmp_color[FLOOR] = call_cub()->map->floor_color;
// 		tmp_color[CEILING] = call_cub()->map->ceiling_color;
// 		modified_color[FLOOR] = tmp_color[FLOOR];
// 		modified_color[CEILING] = tmp_color[CEILING];
// 	}
// 	if (vfx->shadow_enabled)
// 	{
// 		modified_color[FLOOR] = shadow_effect(tmp_color[FLOOR], distance, 0.0f, 3.0f);
// 		modified_color[CEILING] = shadow_effect(tmp_color[CEILING], distance, 0.0f, 3.0f);
// 	}
// 	else if (vfx->fog_enabled)
// 	{
// 		modified_color[FLOOR] = fog_effect(tmp_color[FLOOR], distance, 0.0f, 5.0f, vfx->fog_color);
// 		modified_color[CEILING] = fog_effect(tmp_color[CEILING], distance, 0.0f, 5.0f, vfx->fog_color);
// 	}
// 	else if (vfx->floor_fog_enabled)
// 	{
// 		modified_color[FLOOR] = fog_effect(tmp_color[FLOOR], distance, 0.0f, (3.0f / (1.0f - vfx->floor_fog_level)), vfx->floor_fog_color);
// 		modified_color[CEILING] = fog_effect(tmp_color[CEILING], distance, 0.0f, (3.0f / (1.0f - vfx->floor_fog_level)), vfx->floor_fog_color);
// 	}
// 	*color[FLOOR] = modified_color[FLOOR];
// 	*color[CEILING] = modified_color[CEILING];
// }

// /*
// for floor fog effect, try having a very light fog,
// and for the fog in fog_level, we do it denser?
// maybe will have a smoother contrast...

// idea: layered opacity, gradient effect instead of solid separation line..

// ex: if floor fog level is at the middle of the walls,
// ground level to quarter level will be 100% floor_fog_color,
// quarter level to third level will be 80%, rest up to fog level at 60%.. or something like that

// ** implement another fog function, which plays with the density (so with min, max)

// *** then try combinations with the floor_fog function..

// */

// // void	adjust_shadow(t_vfx *vfx); //tmp test with shadow first, then fog and floor fog
// // {
// // 	// density
// // }

// // void	adjust_fog(t_vfx *vfx); //add color control, and adapt density
// // void	control_fog(t_vfx *vfx); //add base fog level, adapt density with floor fog,
// // try having the fog level from ground up, from ceiling down, from far to close
// // might need subfunctions, ceiling sweep control seems complex..
