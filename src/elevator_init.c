/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevator_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:55:00 by olivierroy        #+#    #+#             */
/*   Updated: 2024/04/10 22:33:34 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	update_elevator_struct(t_cub *cub, t_elevator elevator)
// {
// 	cub->elevator.door = elevator.door;
// 	cub->elevator.door_open = elevator.door_open;
// 	cub->elevator.map_change = elevator.map_change;
// 	cub->elevator.orientation = elevator.orientation;
// 	cub->elevator.position = elevator.position;
// 	cub->elevator.valid = elevator.valid;
// }

// static void	draw_buttons_pixels(t_elevator *e, t_point size, int min, int max)
// {
// 	int color;
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < size.y)
// 	{
// 		x = 0;
// 		while (x < size.x)
// 		{
// 			if (y >= min && y < max)
// 				color = get_pixel(e->texture[E_BTN_ON], x, y % size.x);
// 			else
// 				color = get_pixel(e->texture[E_BTN_OFF], x, y % size.x);
// 			if (get_alpha(color) == 255)
// 				draw_pixel(e->buttons, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	draw_buttons(t_elevator *elevator, int floor_number)
// {
// 	t_point	size;
// 	int		min;
// 	int		max;

// 	size = elevator->buttons_size;
// 	min = size.y - (size.x + floor_number * size.x);
// 	max = size.y - floor_number * size.x;
	
// 	elevator->buttons->instances[0].x = 0;
// 	elevator->buttons->instances[0].y = 0;
// 	draw_buttons_pixels(elevator, size, min, max);
	
// 	elevator->buttons->instances[0].x = WIDTH - size.x;
// 	elevator->buttons->instances[0].y = HEIGHT - size.y;
// }

// static void	set_buttons(t_cub *cub, t_elevator *elevator)
// {
// 	t_point	size;

// 	size.x = 64;
// 	size.y = size.x * cub->scene_total;
// 	elevator->buttons = new_img(cub->mlx, size.x, size.y, true);
// 	elevator->buttons_size = size;
// 	draw_buttons(elevator, 0);
// }

static void	set_elevator_textures(t_cub *cub, t_elevator *elevator)
{
	mlx_image_t	*door_img;

	elevator->texture[E_WALL] = load_png("img/elevator_wall.png", cub->mlx);
	elevator->texture[E_FLOOR] = load_png("img/elevator_floor.png", cub->mlx);
	elevator->texture[E_CEILING] = load_png("img/elevator_ceiling.png", cub->mlx);
	elevator->texture[E_BTN_OFF] = load_png("img/elevator_btn_off.png", cub->mlx);
	elevator->texture[E_BTN_ON] = load_png("img/elevator_btn_on.png", cub->mlx);
	
	door_img = load_png("img/elevator_door.png", cub->mlx);
	elevator->door_animation = set_animation(door_img);
	mlx_delete_image(cub->mlx, door_img);
}

t_elevator	init_elevator(t_cub *cub)
{
	t_elevator	elevator;

	ft_memset(&elevator, 0, sizeof (t_elevator));
	parse_elevator(get_map(cub->current_level), &elevator);
	elevator.user_interface = new_img(cub->mlx, WIDTH, HEIGHT, true); //
	set_elevator_textures(cub, &elevator);
	
	// set_buttons(cub, &elevator);

	return (elevator);
}
