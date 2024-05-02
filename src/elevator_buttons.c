/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevator_buttons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:34:36 by oroy              #+#    #+#             */
/*   Updated: 2024/04/30 15:49:57 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_button_hover(t_button btn[2])
{
	int	x;
	int	y;

	mlx_get_mouse_pos(call_cub()->mlx, &x, &y);
	if (x >= btn[0].position.x && x < btn[0].position.x + btn[0].size.x
		&& y >= btn[0].position.y && y < btn[0].position.y + btn[0].size.y)
		btn[0].button_imgs[1]->instances->enabled = true;
	else
		btn[0].button_imgs[1]->instances->enabled = false;
	if (x >= btn[1].position.x && x < btn[1].position.x + btn[1].size.x
		&& y >= btn[1].position.y && y < btn[1].position.y + btn[1].size.y)
		btn[1].button_imgs[1]->instances->enabled = true;
	else
		btn[1].button_imgs[1]->instances->enabled = false;
}

/*	**do we change button size
*/
static t_button	new_button(t_point pos)
{
	t_button	button;
	mlx_t		*mlx;

	mlx = call_cub()->mlx;
	ft_memset(&button, 0, sizeof(t_button));
	button.button_imgs[OFF] = load_png(E_BTN_OFF_PATH, mlx);
	button.button_imgs[ON] = load_png(E_BTN_ON_PATH, mlx);
	button.button_imgs[OFF]->instances->x = pos.x;
	button.button_imgs[OFF]->instances->y = pos.y;
	button.button_imgs[ON]->instances->x = pos.x;
	button.button_imgs[ON]->instances->y = pos.y;
	button.position = pos;
	button.size = (t_point){BUTTON_SIZE, BUTTON_SIZE};
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
