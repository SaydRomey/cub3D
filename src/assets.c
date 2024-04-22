/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:53:13 by oroy              #+#    #+#             */
/*   Updated: 2024/04/19 16:47:51 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	get_assets_position(t_map map, t_fpoint pos[SPRITE_MAX], int *total)
{
	int	x;
	int	y;

	*total = 0;
	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.map_array[y][x] == 0 && ft_rand(0, 5) == 3)
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
	t_fpoint	position[SPRITE_MAX];
	t_animation	animation;
	t_asset		*assets;
	mlx_image_t	*texture;
	int			i;

	get_assets_position(current_lvl->map, position, &current_lvl->assets_total);
	assets = ft_calloc(current_lvl->assets_total, sizeof (t_asset));
	if (!assets)
		return (NULL);
	i = 0;
	while (i < current_lvl->assets_total)
	{
		assets[i].pos = position[i];
		i++;
	}
	texture = load_png(texture_path, call_cub()->mlx);
	if (!texture)
		return (NULL);
	ft_memset(&animation, 0, sizeof (t_animation));
	if (slice_total > 1)
	{
		animation = set_animation(texture, slice_total);
		mlx_delete_image(call_cub()->mlx, texture);
		texture = animation.frames[0];
	}
	i = 0;
	while (i < current_lvl->assets_total)
	{
		assets[i].anim = animation;
		assets[i].tex = texture;
		i++;
	}
	return (assets);
}
