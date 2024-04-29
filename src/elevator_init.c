/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevator_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:55:00 by olivierroy        #+#    #+#             */
/*   Updated: 2024/04/29 15:08:52 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_elevator_textures(t_cub *cub, t_elevator *elevator)
{
	mlx_image_t	*door_img;

	elevator->texture[E_WALL] = load_png("img/elevator_wall.png", cub->mlx);
	elevator->texture[E_FLOOR] = load_png("img/elevator_floor.png", cub->mlx);
	elevator->texture[E_CEILING] = \
	load_png("img/elevator_ceiling.png", cub->mlx);
	door_img = load_png("img/elevator_door.png", cub->mlx);
	elevator->door_animation = set_animation(door_img, 4);
	mlx_delete_image(cub->mlx, door_img);
}

t_elevator	init_elevator(t_level *lvl)
{
	t_cub		*cub;
	t_elevator	elevator;

	cub = call_cub();
	ft_memset(&elevator, 0, sizeof (t_elevator));
	if (lvl->elevator_exists)
	{
		elevator.position = lvl->elevator_position;
		elevator.orientation = lvl->elevator_orientation;
	}
	set_elevator_textures(cub, &elevator);
	init_buttons(&elevator);
	return (elevator);
}
