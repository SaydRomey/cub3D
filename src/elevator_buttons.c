
// #include "cub3d.h"

// /*
// implement a better way of alternating between the btn_on and btn_off for each of the buttons

// */
// // void	toggle_button(t_button *button, int state)
// // {
// // 	// mlx_set_instance_depth()
// // }

// # define BUTTON_SIZE 64

// t_button    new_button(t_point pos)
// {
// 	t_button    button;

// 	ft_memset(&button, 0, sizeof(t_button)); //sets the state to OFF

// 	button.button_imgs[OFF] = load_png("img/elevator_btn_off.png", call_cub()->mlx);
// 	button.button_imgs[ON] = load_png("img/elevator_btn_on.png", call_cub()->mlx);

// 	button.position = pos;
// 	button.size = (t_point){64, 64}; //change to fit an image size..?

// 	return (button);
// }

// void    init_buttons(t_elevator *elevator)
// {
// 	int		up;
// 	int		down;
// 	int		margin;
// 	t_point	position;

// 	up = 0;
// 	down = 1;
// 	margin = 20;

// 	position.x = WIDTH - margin - BUTTON_SIZE;
// 	position.y = HEIGHT - margin - (BUTTON_SIZE * 2);
// 	elevator->buttons[up] = new_button(position);

// 	position.x = WIDTH - margin - BUTTON_SIZE;
// 	position.y = HEIGHT - margin - BUTTON_SIZE;
// 	elevator->buttons[down] = new_button(position);

// }

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
