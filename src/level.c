/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:21:17 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/01 21:50:04 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_elevator_info(t_level *lvl, t_map *map)
{
	t_point	*pos;

	pos = &lvl->elevator_position;
	lvl->elevator_exists = find_value_in_array(map, ELEVATOR, pos);
	if (lvl->elevator_exists)
		lvl->elevator_orientation = \
	get_elevator_orientation(map->map_array, pos);
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
		if (lvl->is_segworld || lvl->assets)
			cleanup_asset(lvl->assets);
		mlx_delete_image(call_cub()->mlx, lvl->mini.img);
		free(lvl);
	}
}
