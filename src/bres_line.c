/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bres_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:16:40 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/26 13:18:13 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
to put in libft ?
*/
static int	ft_signum(int start, int end)
{
	if (start < end)
		return (1);
	if (start > end)
		return (-1);
	return (0);
}

static t_point	get_direction(t_point start, t_point end)
{
	t_point	direction;

	direction.x = ft_signum(start.x, end.x);
	direction.y = ft_signum(start.y, end.y);
	return (direction);
}

static t_point	get_distance(t_point start, t_point end)
{
	t_point	distance;

	distance.x = ft_abs(end.x - start.x);
	distance.y = ft_abs(end.y - start.y);
	return (distance);
}

static int	calculate_initial_error(t_point distance)
{
	if (distance.x > distance.y)
		return (distance.x / 2);
	else
		return (-distance.y / 2);
}

/*
bresenham's line algorithm
*/
void	bres_line(mlx_image_t *img, t_point start, t_point end, int color)
{
	t_point	direction;
	t_point	distance;
	int		error;
	int		error_tmp;
	
	direction = get_direction(start, end);
	distance = get_distance(start, end);
	error = calculate_initial_error(distance);
	while (TRUE)
	{
		draw_pixel(img, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		error_tmp = error;
		if (error_tmp > -distance.x)
		{
			error -= distance.y;
			start.x += direction.x;
		}
		if (error_tmp < distance.y)
		{
			error += distance.x;
			start.y += direction.y;
		}
	}
}
