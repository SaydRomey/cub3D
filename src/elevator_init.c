/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevator_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:55:00 by olivierroy        #+#    #+#             */
/*   Updated: 2024/04/29 21:22:36 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_elevator_struct(void)
{
	t_cub	*cub;
	t_level	*lvl;

	cub = call_cub();
	lvl = get_level(cub->current_level);
	cub->elevator.map_change = 0;
	cub->elevator.orientation = lvl->elevator_orientation;
	cub->elevator.position = lvl->elevator_position;
}

static void	set_elevator_textures(t_cub *cub, t_elevator *elevator)
{
	mlx_image_t	*door_img;

	elevator->texture[E_WALL] = load_png("img/elevator_wall.png", cub->mlx);
	elevator->texture[E_FLOOR] = load_png("img/elevator_floor.png", cub->mlx);
	elevator->texture[E_CEILING] = load_png("img/elevator_ceiling.png", cub->mlx);
	door_img = load_png("img/elevator_door.png", cub->mlx);
	elevator->door_animation = set_animation(door_img, 4);
	mlx_delete_image(cub->mlx, door_img);
}

t_elevator	init_elevator(t_cub *cub)
{
	t_elevator	elevator;

	ft_memset(&elevator, 0, sizeof (t_elevator));
	elevator.valid = true;
	
	parse_elevator(get_map(cub->current_level), &elevator);
	set_elevator_textures(cub, &elevator);

	init_buttons(&elevator);

	return (elevator);
}
