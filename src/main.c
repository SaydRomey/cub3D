/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/20 17:11:53 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(void)
{
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR);
	exit(FAILURE);
}

t_cub	init_cub(char *map_path)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	char		*title;

	title = ft_strjoin("cub3D - ", map_path);
	mlx = mlx_init(WIDTH, HEIGHT, title, FALSE);
	if (!mlx)
		error();
	free(title);

	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		error();
	
	return ((t_cub){mlx, img});
}

void	cub_loop(t_cub *cub)
{
	// hooks
	
	mlx_loop(cub->mlx);
}

int	main(void)
{
	t_cub	cub;
	int		test; // unused variable to test makefile target 'make force'

	cub = init_cub("[map title]");

	if (mlx_image_to_window(cub.mlx, cub.img, 0, 0) < SUCCESS)
		error();

	cub_loop(&cub);

	mlx_delete_image(cub.mlx, cub.img);
	mlx_terminate(cub.mlx);

	return (SUCCESS);
}
