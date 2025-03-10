/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:34:28 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/01 21:44:06 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSET_H
# define ASSET_H

# include "MLX42.h"
# include "animations.h"
# include "map.h"

# define SPRITE_MAX	32

# define A_FLAMES_PATH	"img/assets/flames.png"

/*
*/
typedef struct s_asset
{
	float		distance;
	int			screen_x;
	t_fpoint	pos;
	t_fpoint	pos_relative;
	t_fpoint	tf;
	t_line		h;
	t_line		v;
	mlx_image_t	*tex;
	t_animation	anim;
	bool		is_animated;
}				t_asset;

// assets_utils.c
void	cleanup_asset(t_asset *asset);
void	asset_pixel(mlx_image_t *img, int x, int y, int color);
bool	is_near_elevator(t_map *map, int x, int y);

// assets.c
t_asset	*init_assets(char *texture_path, void *param, int slice_total);
void	update_assets(void *param);

#endif // ASSET_H
