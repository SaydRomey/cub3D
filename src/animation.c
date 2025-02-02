/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:29:55 by olivierroy        #+#    #+#             */
/*   Updated: 2024/05/01 22:22:27 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_frame(t_animation *anim, mlx_image_t *img, t_slice slice, int i)
{
	mlx_image_t	*frame;
	int			color;
	int			x;
	int			y;

	frame = mlx_new_image(call_cub()->mlx, slice.width, slice.height);
	if (!frame)
	{
		set_error("MLX Image error");
		error();
	}
	y = 0;
	while (y < slice.height)
	{
		x = 0;
		while (x < slice.width)
		{
			color = get_pixel(img, slice.position.x + x, slice.position.y + y);
			draw_pixel(frame, x, y, color);
			x++;
		}
		y++;
	}
	anim->frames[i] = frame;
}

static t_animation	get_frames_from_image(mlx_image_t *img, t_slice slice)
{
	t_animation	anim;
	int			i;

	i = 0;
	ft_memset(&anim, 0, sizeof (t_animation));
	anim.frames = ft_calloc(slice.total, sizeof (mlx_image_t *));
	if (!anim.frames)
	{
		set_error("Malloc error");
		error();
	}
	while (i < slice.total)
	{
		add_frame(&anim, img, slice, i);
		slice.position.x += slice.width;
		i++;
	}
	anim.last_frame = i - 1;
	return (anim);
}

static t_slice	get_slice_info(mlx_image_t *img, int slice_total)
{
	t_slice	slice;

	slice.position.x = 0;
	slice.position.y = 0;
	slice.total = slice_total;
	slice.width = img->width / slice.total;
	slice.height = img->height;
	return (slice);
}

t_animation	set_animation(mlx_image_t *img, int slice_total)
{
	t_animation	anim;
	t_slice		slice;

	slice = get_slice_info(img, slice_total);
	anim = get_frames_from_image(img, slice);
	anim.frame_speed = FRAME_SPEED;
	return (anim);
}

void	update_animation(t_animation *a, bool direction)
{
	a->accumulator += call_cub()->mlx->delta_time * 1000;
	if (a->accumulator > a->frame_speed)
	{
		a->accumulator -= a->frame_speed;
		if (direction == GO_RIGHT)
		{
			a->current_frame++;
			if (a->current_frame > a->last_frame)
				a->current_frame = 0;
		}
		else
		{
			a->current_frame--;
			if (a->current_frame < 0)
				a->current_frame = a->last_frame;
		}
	}
}
