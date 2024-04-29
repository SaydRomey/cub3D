/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:27:46 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/29 15:36:34 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "MLX42.h"
# include "utils.h"
# include "math_utils.h"
# include "map.h"

// draw_circle.c
void	draw_circle(mlx_image_t *img, t_circle circle);
void	draw_circle_hollow(mlx_image_t *img, t_circle circle, int thickness);

// draw_triangle.c
void	draw_triangle(mlx_image_t *img, t_triangle *tri, int color);
void	draw_triangle_hollow(mlx_image_t *img, t_triangle *tri, \
int thickness, int color);

// draw.c
void	draw_line(mlx_image_t *img, t_fpoint start, t_fpoint end, int color);
void	draw_rectangle(mlx_image_t *img, \
t_point origin, t_point end, int color);
void	draw_random_rectangle(mlx_image_t *img, \
t_point origin, t_point end, int brightness_level);
void	draw_floor_ceiling(mlx_image_t *img, t_map *map);

#endif // DRAW_H
