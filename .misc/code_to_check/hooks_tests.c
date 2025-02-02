/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:19:14 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/10 12:20:44 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

testing the 'modifier' for keys
*/
void	key_modifier_hook(mlx_key_data_t keydata, void* param)
{
    (void)param;
	if (keydata.key == MLX_KEY_SPACE \
    && keydata.action == MLX_RELEASE \
    && keydata.modifier == MLX_CONTROL)
		printf("ctrl + space released\n");
}

void    key_action_test(mlx_key_data_t keydata, void *param)
{
    mlx_t *mlx;
    
    mlx = (mlx_t *)param;
    if (keydata.key == MLX_KEY_ESCAPE \
    && keydata.action == MLX_PRESS)
        mlx_set_window_title(mlx, "esc pressed");
    if (keydata.key == MLX_KEY_ESCAPE \
    && keydata.action == MLX_RELEASE)
        mlx_set_window_title(mlx, TITLE);
// 
    if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
        printf("key 1 pressed\n");
    if (keydata.key == MLX_KEY_2 && keydata.action == MLX_RELEASE)
        printf("key 2 released\n");
    if (keydata.key == MLX_KEY_3 && keydata.action == MLX_REPEAT)
        printf("key 3 repeated\n"); //hold
}

/* ************************************************************************** */
/* ***************************** scroll hooks ******************************* */

/*
invert-slide the image with touchpad
(need to test with xy scrolling mouse)
*/
void    scroll_move_img(double xdelta, double ydelta, void *param)
{
    mlx_image_t *img;
    
    img = (mlx_image_t *)param;
    if (ydelta > 0 && img->instances[0].y)
        img->instances[0].y += 10;
    else if (ydelta < 0)
        img->instances[0].y -= 10;
    if (xdelta > 0)
        img->instances[0].x += 10;
    else if (xdelta < 0)
        img->instances[0].x -= 10;
}

void    scroll_title_test(double xdelta, double ydelta, void *param)
{
    mlx_t *mlx;

    mlx = (mlx_t *)param;
    // printf("x = %f\n", xdelta);
    // printf("y = %f\n", ydelta);
    if (ydelta > 0)
        mlx_set_window_title(mlx, "scroll up");
    else if (ydelta < 0)
        mlx_set_window_title(mlx, "scroll down");
    if (xdelta < 0)
        mlx_set_window_title(mlx, "scroll right");
    else if (xdelta > 0)
        mlx_set_window_title(mlx, "scroll left");
}
