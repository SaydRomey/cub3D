/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:21:17 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/25 13:44:53 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_elevator(t_elevator *elevator, t_level *lvl)
{
	// if (!lvl->elevator_exists)
	// 	replace_with_segworld(lvl);
	elevator->map_change = 0;
	elevator->orientation = lvl->elevator_orientation;
	elevator->position = lvl->elevator_position;
}

static t_player	warp_player(t_player old_player, \
							t_level *lvl, t_level *next_lvl)
{
	t_player	player;
	t_fpoint	pos;
	int			rotation;

	player = old_player;
	pos.x = player.position.x - lvl->elevator_position.x;
	pos.y = player.position.y - lvl->elevator_position.y;
	rotation = next_lvl->elevator_orientation - lvl->elevator_orientation;
	if (rotation)
	{
		pos = rotate_vector_position(pos, rotation);
		player.delta = rotate_vector_delta(player.delta, -rotation);
		player.cam_plane.x = -player.delta.y * player.fov;
		player.cam_plane.y = player.delta.x * player.fov;
	}
	player.position.x = next_lvl->elevator_position.x + pos.x;
	player.position.y = next_lvl->elevator_position.y + pos.y;
	return (player);
}

void	change_level(int index)
{
	t_cub	*cub;
	t_level	*lvl;
	t_level	*next_lvl;

	cub = call_cub();
	if (cub->current_level == index)
		return ;
	next_lvl = get_level(index);
	lvl = get_level(cub->current_level);
	if (lvl && next_lvl)
	{
		if (!next_lvl->elevator_exists)
			replace_with_segworld(next_lvl);
		change_window_title(next_lvl->filepath);
		lvl->mini.img->instances->enabled = false;
		draw_minimap(&next_lvl->mini, &next_lvl->map);
		draw_floor_ceiling(cub->img, &next_lvl->map);
		cub->current_level = index;
		cub->player = warp_player(cub->player, lvl, next_lvl);
		update_elevator(&cub->elevator, next_lvl);
	}
	// error if no next lvl ?
	return ;
}

/* ************************************************************************** */

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
