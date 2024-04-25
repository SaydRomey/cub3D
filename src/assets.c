/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:53:13 by oroy              #+#    #+#             */
/*   Updated: 2024/04/24 20:52:29 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Go through all assets and update their texture based on the animation.
 * 
 * To do: Test if it's better to point to animation instead of stacking them.
*/
void	update_assets(t_cub *cub)
{
	t_level	*current;
	int		idx;
	int		i;

	current = get_level(cub->current_level);
	if (current->assets) // && current->assets->anim
	{
		i = 0;
		while (i < current->assets_total)
		{
			update_animation(&current->assets[i].anim, GO_RIGHT);
			idx = current->assets[i].anim.current_frame;
			current->assets[i].tex = current->assets[i].anim.frames[idx];
			i++;
		}
	}
}

static void	set_anim_and_tex(t_asset *assets, int total, char *path, int slices)
{
	t_animation	animation;
	mlx_image_t	*texture;
	int			i;

	texture = load_png(path, call_cub()->mlx);
	ft_memset(&animation, 0, sizeof (t_animation));
	if (slices > 1)
	{
		animation = set_animation(texture, slices);
		mlx_delete_image(call_cub()->mlx, texture);
		texture = animation.frames[0];
	}
	i = 0;
	while (i < total)
	{
		assets[i].anim = animation;
		assets[i].tex = texture;
		i++;
	}
}

static void	get_assets_pos(t_map *map, t_fpoint pos[SPRITE_MAX], int *total)
{
	int	x;
	int	y;

	*total = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map_array[y][x] == 0
				&& !is_near_elevator(map, x, y)
				&& ft_rand(0, 5) == 3)
			{
				pos[*total] = (t_fpoint){x + 0.5, y + 0.5};
				(*total)++;
			}
			x++;
		}
		y++;
	}
}

t_asset	*init_assets(char *texture_path, t_level *current_lvl, int slice_total)
{
	t_fpoint	pos[SPRITE_MAX];
	t_asset		*assets;
	int			assets_total;
	int			i;

	get_assets_pos(&current_lvl->map, pos, &current_lvl->assets_total);
	assets = ft_calloc(current_lvl->assets_total, sizeof (t_asset));
	if (!assets)
		return (NULL);
	i = 0;
	assets_total = current_lvl->assets_total;
	while (i < assets_total)
	{
		assets[i].pos = pos[i];
		i++;
	}
	set_anim_and_tex(assets, assets_total, texture_path, slice_total);
	return (assets);
}
