/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevator_map_change.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:43:16 by oroy              #+#    #+#             */
/*   Updated: 2024/03/31 11:19:32 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_fpoint	rotate_vector_position(t_fpoint tmp, int rotation)
{
	t_fpoint	new;

	if (rotation == -90 || rotation == 270)
	{
		new.x = 1 - tmp.y;
		new.y = tmp.x;
	}
	else if (rotation == 90 || rotation == -270)
	{
		new.x = tmp.y;
		new.y = 1 - tmp.x;
	}
	else
	{
		new.x = 1 - tmp.x;
		new.y = 1 - tmp.y;
	}
	return (new);
}

static t_fpoint	rotate_vector_delta(t_fpoint tmp, int rotation)
{
	t_fpoint	new;

	if (rotation == -90 || rotation == 270)
	{
		new.x = tmp.y;
		new.y = -tmp.x;
	}
	else if (rotation == 90 || rotation == -270)
	{
		new.x = -tmp.y;
		new.y = tmp.x;
	}
	else
	{
		new.x = -tmp.x;
		new.y = -tmp.y;
	}
	return (new);
}

static int	get_angle(int orientation)
{
	if (orientation == NO)
		return (90);
	if (orientation == SO)
		return (270);
	if (orientation == EA)
		return (0);
	if (orientation == WE)
		return (180);
	return (-1);
}

static void	change_character_coordinates(t_cub *cub, t_fpoint pos, int ori_old)
{
	int	rotation;

	rotation = get_angle(cub->elevator.orientation) - get_angle(ori_old);
	if (rotation)
	{
		pos = rotate_vector_position(pos, rotation);
		cub->player.delta = rotate_vector_delta(cub->player.delta, -rotation);
		cub->player.cam_plane.x = -cub->player.delta.y * cub->player.fov;
		cub->player.cam_plane.y = cub->player.delta.x * cub->player.fov;
	}
	cub->player.position.x = cub->elevator.position.x + pos.x;
	cub->player.position.y = cub->elevator.position.y + pos.y;
}

void	change_map(t_cub *cub)
{
	t_elevator	elevator;
	t_fpoint	pos;
	int			ori;

	pos.x = cub->player.position.x - cub->elevator.position.x;
	pos.y = cub->player.position.y - cub->elevator.position.y;
	ori = cub->elevator.orientation;
	// retrieve_scene(cub, cub->paths[cub->elevator.id]);
	parse_elevator(&cub->maps[cub->elevator.id], &elevator);
	if (elevator.valid)
	{
		cub->map = &cub->maps[cub->elevator.id];
		update_elevator_struct(cub, elevator);
		change_character_coordinates(cub, pos, ori);
	}
	// else
	// {
	// 	// Call Segworld
	// 	call_segworld(cub, &elevator, pos, ori);
	// }
}