/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:34:06 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/13 11:05:02 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlx	*call_mlx(void)
{
	static t_mlx	*info;

	if (info == NULL)
	{
		info = malloc(sizeof(t_info));
		if (!info)
			// return (set_error_msg(ERR_MALLOC), NULL);
			return (NULL);
	}
	return (info);
}

void	setup_mlx(char *str)
{
	t_mlx	*info;
	char	*title;

	info = call_mlx();
	title = ft_strjoin("cub3D - ", str);
	info.mlx_ptr = mlx_init();
	info.win_ptr = mlx_new_window(info.mlx_ptr, WIDTH, HEIGHT, title);
	safe_free((void **)&title); //or just free ?
	info.img.img_ptr = mlx_new_image(info.mlx_ptr, WIDTH, HEIGHT);
	info.img.addr = mlx_get_data_addr(info.mlx_ptr, &info.img.bpp,
		&info.img.line_length, &info.img.endian);
}

void	

void	loop_mlx(void)
{
	t_mlx	*info;

	info = call_info();
	render(info);
	hooks(info);
	mlx_loop(info->mlx_ptr);
}

/*
will need to be different for mac/windows
this is linux version, for mac, remove the 3 'mlx_*' functions
*/
int	terminate_mlx(void)
{
	t_mlx	*info;

	info = call_mlx();
	// [insert function that frees the rest later]
	if (info.img.img_ptr)
		mlx_destroy_image(info->mlx_ptr, info->img.img_ptr);
	if (info.win_ptr)
		mlx_destroy_window(info->mlx_ptr, info->win_ptr);
	mlx_destroy_display(info->mlx_ptr);
	safe_free((void **)&info->mlx_ptr);
	exit(SUCESS); //is it an allowed function ?
}