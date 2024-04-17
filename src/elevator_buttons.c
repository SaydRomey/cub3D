/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevator_buttons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:34:36 by oroy              #+#    #+#             */
/*   Updated: 2024/04/17 01:11:12 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// /*
// implement a better way of alternating between the btn_on and btn_off for each of the buttons

// */
// // void	toggle_button(t_button *button, int state)
// // {
// // 	// mlx_set_instance_depth()
// // }

void	check_button_hover(t_button btn[2])
{
	int	x;
	int	y;

	mlx_get_mouse_pos(call_cub()->mlx, &x, &y);

	if (x >= btn[0].position.x && x < btn[0].position.x + btn[0].size.x &&
		y >= btn[0].position.y && y < btn[0].position.y + btn[0].size.y)
		btn[0].button_imgs[1]->instances->enabled = true;
	else
		btn[0].button_imgs[1]->instances->enabled = false;

	if (x >= btn[1].position.x && x < btn[1].position.x + btn[1].size.x &&
		y >= btn[1].position.y && y < btn[1].position.y + btn[1].size.y)
		btn[1].button_imgs[1]->instances->enabled = true;
	else
		btn[1].button_imgs[1]->instances->enabled = false;
}

static t_button	new_button(t_point pos)
{
	t_button    button;
	mlx_t		*mlx;

	mlx = call_cub()->mlx;

	ft_memset(&button, 0, sizeof(t_button)); //sets the state to OFF

	button.button_imgs[OFF] = load_png("img/elevator_btn_off.png", mlx);
	button.button_imgs[ON] = load_png("img/elevator_btn_on.png", mlx);

	button.button_imgs[OFF]->instances->x = pos.x;
	button.button_imgs[OFF]->instances->y = pos.y;
	button.button_imgs[ON]->instances->x = pos.x;
	button.button_imgs[ON]->instances->y = pos.y;

	button.position = pos;
	button.size = (t_point){64, 64}; //change to fit an image size..?

	return (button);
}

void	init_buttons(t_elevator *elevator)
{
	int		up;
	int		down;
	int		margin;
	t_point	position;

	up = 0;
	down = 1;
	margin = 20;

	position.x = WIDTH - margin - BUTTON_SIZE;
	position.y = HEIGHT - margin - (BUTTON_SIZE * 2);
	elevator->buttons[up] = new_button(position);

	position.x = WIDTH - margin - BUTTON_SIZE;
	position.y = HEIGHT - margin - BUTTON_SIZE;
	elevator->buttons[down] = new_button(position);
}

// static void	draw_button(mlx_image_t *img, t_point origin, t_point size, bool state, int index)
// {
// 	int	x;
// 	int	y;
// 	int color;

// 	y = 0;
// 	while (y < size.y)
// 	{
// 		x = 0;
// 		while (x < size.x)
// 		{
// 			color = get_pixel(call_cub()->elevator.buttons[index].button_imgs[state], x, y);
// 			draw_pixel(img, origin.x + x, origin.y + y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }


// void    test_buttons(t_elevator *elevator)
// {

// 	init_buttons(elevator);

// 	draw_button(call_cub()->user_interface, elevator->buttons[0].position, elevator->buttons[0].size, elevator->buttons[0].state, 0);
// 	draw_button(call_cub()->user_interface, elevator->buttons[1].position, elevator->buttons[1].size, elevator->buttons[1].state, 1);
// }


// // draw_button_img(); //draw a full image_t for the ui
