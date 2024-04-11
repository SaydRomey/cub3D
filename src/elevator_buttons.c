
#include "cub3d.h"

t_button    new_button(t_point pos)
{
	t_button    button;

	// ft_memset(button, 0, sizeof(t_button));

	button.button_imgs[0] = load_png("img/elevator_btn_off.png", call_cub()->mlx);
	button.button_imgs[1] = load_png("img/elevator_btn_on.png", call_cub()->mlx);

	button.position = pos;
	button.size = (t_point){64, 64}; //change to fit an image size..?

	return (button);
}

void    init_buttons(t_elevator *elevator)
{
	int up = 0;
	int down = 1;

	t_point margin = {20, 20};

	t_point up_button_pos = {WIDTH - margin.x - 64, HEIGHT - margin.y - 64 - 64};
	elevator->buttons[up] = new_button(up_button_pos);
	elevator->buttons[up].state = ON;

	t_point down_button_pos = {WIDTH - margin.x - 64, HEIGHT - margin.y - 64};
	elevator->buttons[down] = new_button(down_button_pos);
	elevator->buttons[down].state = OFF;
}

static void	draw_button(mlx_image_t *img, t_point origin, t_point size, bool state, int index)
{
	int	x;
	int	y;
	int color;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			color = get_pixel(call_cub()->elevator.buttons[index].button_imgs[state], x, y);
			draw_pixel(img, origin.x + x, origin.y + y, color);
			x++;
		}
		y++;
	}
}


void    test_buttons(t_elevator *elevator)
{

	init_buttons(elevator);

	draw_button(elevator->user_interface, elevator->buttons[0].position, elevator->buttons[0].size, elevator->buttons[0].state, 0);
	draw_button(elevator->user_interface, elevator->buttons[1].position, elevator->buttons[1].size, elevator->buttons[1].state, 1);
}


// draw_button_img(); //draw a full image_t for the ui
