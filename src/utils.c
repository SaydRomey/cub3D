/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:39:37 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/02 12:02:42 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cardinal_to_radian(char cardinal)
{
	if (cardinal == 'N')
		return (90);
	if (cardinal == 'S')
		return (270);
	if (cardinal == 'E')
		return (0);
	if (cardinal == 'W')
		return (180);
	return (-1);
}

void	toggle(bool *choice)
{
	if (*choice == ON)
		*choice = OFF;
	else
		*choice = ON;
}

void	change_window_title(char *filepath)
{
	char	*title;

	title = ft_strjoin("cub3D - ", filepath);
	mlx_set_window_title(call_cub()->mlx, title);
	free(title);
}

void	display_menu(mlx_image_t *img)
{
	t_keys	keys;
	int		menu_height;
	int		menu_show;
	int		menu_hide;

	menu_height = (int)img->height;
	menu_show = HEIGHT - menu_height;
	menu_hide = HEIGHT - 85;
	keys = call_cub()->keys;
	if (keys.spacebar && img->instances->y != menu_show)
		move_img(img, 0, menu_show);
	if (!keys.spacebar && img->instances->y != menu_hide)
		move_img(img, 0, menu_hide);
}
