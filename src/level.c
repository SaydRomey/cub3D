/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:21:17 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/22 14:38:31 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	update_elevator(t_elevator *elevator, t_level *lvl)
// {
// 	elevator->map_change = 0;
// 	elevator->orientation = lvl->elevator_orientation;
// 	elevator->position = lvl->elevator_position;
// }


void	change_level(int index)
{
	t_cub	*cub;
	t_level	*lvl;
	t_level	*next_lvl;

	cub = call_cub();
	if (cub->current_level == index)
		return ;
	next_lvl = get_level(index);
	if (next_lvl)
	{
		if (!next_lvl->elevator_exists)
			replace_with_segworld(next_lvl);
		lvl = get_level(cub->current_level);
		lvl->mini.img->instances->enabled = false;
		change_window_title(next_lvl->filepath);
		draw_minimap(&next_lvl->mini, &next_lvl->map);
		cub->current_level = index;
		cub->player = warp_player(cub->player, lvl, next_lvl);
	}
	return ;
}

/* ************************************************************************** */
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

void	add_new_level(t_list **levels, t_map map, char *filepath)
{
	t_level	*new_level;
	t_list	*node;

	new_level = (t_level *)ft_calloc(1, sizeof(t_level));
	if (!new_level)
	{
		set_error("Malloc error");
		return ;
	}
	new_level->filepath = filepath;
	new_level->index = ft_lstsize(*levels);
	new_level->map = deep_copy_map(map);
	new_level->mini = init_minimap(&map);
	get_elevator_info(new_level, &map);
	node = ft_lstnew(new_level);
	if (!node)
	{
		delete_level(new_level);
		set_error("Malloc error");
		return ;
	}
	ft_lstadd_back(levels, node);
}

void	delete_level(void *level)
{
	t_level	*lvl;

	lvl = (t_level *)level;
	if (lvl)
	{
		cleanup_map(&lvl->map);
		mlx_delete_image(call_cub()->mlx, lvl->mini.img);
		free(lvl);
	}
}

/* ************************************************************************** */
/* ************************************************************************** */

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

t_minimap	*get_minimap(int index)
{
	t_level	*lvl;

	lvl = get_level(index);
	if (!lvl)
		return (NULL);
	return (&lvl->mini);
}
