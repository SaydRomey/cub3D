/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:36:14 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/29 15:12:05 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_shadow
{
	bool	enabled;
	float	density;
	float	max;

	// bool	flashlight; maybe a class itself, with enabled(on/off), range, light color, battery level?
}			t_shadow;

typedef struct s_fog
{
	bool	enabled;
	int		color;
	float	density;
	float	max;
}			t_fog;

typedef struct s_vfx
{
	bool	textures_enabled; //add a separate flag for floor/celing ?
	
	
	t_shadow	shadow;
	
	bool	shadow_enabled;
	float	shadow_intensity; //?
	float	shadow_min; //?
	float	shadow_max; //?
	
	
	t_fog	fog;
	
	bool	fog_enabled; //fog effect on walls, floor and ceiling **(if no textures, adapt draw_floor and draw_ceiling)
	int		fog_color;
	bool	floor_fog_enabled; //fog effect on floor and a portion of walls *(can exist without 'fog_enabled also)
	float	floor_fog_level; //defines how high on the wall the floor fog goes [0.0f is none, 1.0f is all the way up]
	int		floor_fog_color;
	
}			t_vfx;


static float	normalize_fog(float distance, float min, float max)
{
	float	clamped_dist;
	float	normalized_dist;

	clamped_dist = ft_fclamp(distance, min, max);
	normalized_dist = (clamped_dist - min) / (max - min);
	return (normalized_dist);
}

int	lerp_color(int color1, int color2, float factor)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = (int)ft_lerp(get_red(color1), get_red(color2), factor);
	green = (int)ft_lerp(get_green(color1), get_green(color2), factor);
	blue = (int)ft_lerp(get_blue(color1), get_blue(color2), factor);
	alpha = (int)ft_lerp(get_alpha(color1), get_alpha(color2), factor);
	return (combine_rgba(red, green, blue, alpha));
}

int	fog_effect(int color, float raw_dist, float min, float max, int fog_color)
{
	float	dist;

	dist = normalize_fog(raw_dist, min, max);
	return (lerp_color(color, fog_color, dist));
}

/* ************************************************************************** */
static int	blend_colors(int color1, int color2, float factor)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	factor = ft_fclamp(factor, 0.0f, 1.0f);
	red = (int)ft_lerp(get_red(color1), get_red(color2), factor);
	green = (int)ft_lerp(get_green(color1), get_green(color2), factor);
	blue = (int)ft_lerp(get_blue(color1), get_blue(color2), factor);
	alpha = (int)get_alpha(color1);
	return (combine_rgba(red, green, blue, alpha));
}

int	fog_effect2(int color, float distance)
{
	t_fog	*fog;
	float	factor;

	fog = &call_cub()->vfx.fog;
	factor = distance / fog->max;
	factor = ft_fclamp(factor, 0.0f, 1.0f);
	return (blend_colors(color, fog->color, factor));
}


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
