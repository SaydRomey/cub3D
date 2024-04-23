/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:46:06 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/22 18:49:43 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_level	*get_level(int index)
{
	t_list	*node;
	t_level	*lvl;

	node = ft_lstget(call_cub()->levels, index);
	if (!node)
		return (NULL);
	lvl = (t_level *)node->content;
	if (!lvl)
		return (NULL);
	return (lvl);
}

t_map	*get_map(int index)
{
	t_level	*lvl;

	lvl = get_level(index);
	if (!lvl)
		return (NULL);
	return (&lvl->map);
}

/* ************************************************************************** */

static void	copy_map_images(t_map *original, t_map *copy)
{
	mlx_t	*mlx;
	int		i;

	mlx = call_cub()->mlx;
	i = 0;
	while (i < ft_max(WALL_TEXTURE_LEN, COLOR_TYPE_LEN))
	{
		if (i < COLOR_TYPE_LEN && original->floor_ceiling_img[i])
			copy->floor_ceiling_img[i] = \
		copy_img(original->floor_ceiling_img[i], mlx);
		if (i < WALL_TEXTURE_LEN && original->wall_textures_img[i])
			copy->wall_textures_img[i] = \
		copy_img(original->wall_textures_img[i], mlx);
		i++;
	}
}

static void	copy_map_array(t_map *original, t_map *copy)
{
	int		i;
	size_t	n;

	n = original->width * sizeof(int);
	if (original->map_array != NULL)
	{
		copy->map_array = allocate_grid(original->height, original->width);
		if (copy->map_array != NULL)
		{
			i = 0;
			while (i < original->height)
			{
				ft_memcpy(copy->map_array[i], original->map_array[i], n);
				i++;
			}
		}
	}
}

t_map	deep_copy_map(t_map original)
{
	t_map	copy;

	copy = original;
	copy_map_array(&original, &copy);
	copy_map_images(&original, &copy);
	return (copy);
}
