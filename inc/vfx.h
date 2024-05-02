/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:57:53 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/02 11:42:05 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VFX_H
# define VFX_H

typedef struct s_vfx
{
	bool	textures_enabled;
	bool	shadow_enabled;	
}			t_vfx;

// shadow.c
int		shadow_effect(int color, float raw_dist, float min, float max);

#endif // VFX_H
