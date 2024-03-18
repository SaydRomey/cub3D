/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_iso.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:41:04 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/17 13:00:15 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define OFFSET 42

void	isoform(t_fpoint *point, int offset)
{
	t_fpoint	tmp;

	if (!point)
		return ;
	tmp.x = point->x;
	tmp.y = point->y;
	
	point->x = (tmp.x - tmp.y) * cos(ISO_ANGLE);
	point->y = (tmp.x + tmp.y) * sin(ISO_ANGLE);

	// point->x = (tmp.x - tmp.y);
	// point->y = (tmp.x + tmp.y) / 2;
	
	point->x += offset;
}

static void	iso_4(t_fpoint *a, t_fpoint *b, t_fpoint *c, t_fpoint *d, int offset)
{
	isoform(a, offset);
	isoform(b, offset);
	isoform(c, offset);
	isoform(d, offset);
}

static void	draw_square(mlx_image_t *img, t_fpoint a, t_fpoint b, t_fpoint c, t_fpoint d, int color)
{
	draw_line(img, a, b, color);
	draw_line(img, b, d, color);
	draw_line(img, a, c, color);
	draw_line(img, c, d, color);
}

void	iso_tile(mlx_image_t *img, t_fpoint origin, int unit_size, int offset, int color)
{
	float	x = (float)origin.x;
	float	y = (float)origin.y;
	int		u = unit_size;
	
	t_fpoint	a = {x, y};
	t_fpoint	b = {x + u, y};
	t_fpoint	c = {x, y + u};
	t_fpoint	d = {x + u, y + u};
	draw_square(img, a, b, c, d, HEX_GRAY); //base in cartesian
	iso_4(&a, &b, &c, &d, offset);
	draw_square(img, a, b, c, d, color);
}

void	iso_cube_seethrough(mlx_image_t *img, t_fpoint origin, int unit_size, int offset, int color)
{
	float	x = (float)origin.x;
	float	y = (float)origin.y;
	int		u = unit_size;
	
	t_fpoint	a = {x, y};
	t_fpoint	b = {x + u, y};
	t_fpoint	c = {x, y + u};
	t_fpoint	d = {x + u, y + u};
	draw_square(img, a, b, c, d, HEX_GRAY); //base in cartesian
	iso_4(&a, &b, &c, &d, offset);
	draw_square(img, a, b, c, d, color);
	
	t_fpoint	a1 = {a.x, a.y - u};
	t_fpoint	b1 = {b.x, b.y - u};
	t_fpoint	c1 = {c.x, c.y - u};
	t_fpoint	d1 = {d.x, d.y - u};
	draw_line(img, a, a1, color);
	draw_line(img, b, b1, color);
	draw_line(img, c, c1, color);
	draw_line(img, d, d1, color);

	draw_square(img, a1, b1, c1, d1, color);
}

void	iso_cube_opaque(mlx_image_t *img, t_fpoint origin, int unit_size, int offset, int color)
{
	float	x = (float)origin.x;
	float	y = (float)origin.y;
	int		u = unit_size;
	
	t_fpoint	a = {x, y};
	t_fpoint	b = {x + u, y};
	t_fpoint	c = {x, y + u};
	t_fpoint	d = {x + u, y + u};
	draw_square(img, a, b, c, d, HEX_GRAY); //base in cartesian
	iso_4(&a, &b, &c, &d, offset);

	// draw_line(img, a, b, color);
	draw_line(img, b, d, color);
	// draw_line(img, a, c, color);
	draw_line(img, c, d, color);
		
	t_fpoint	a1 = {a.x, a.y - u};
	t_fpoint	b1 = {b.x, b.y - u};
	t_fpoint	c1 = {c.x, c.y - u};
	t_fpoint	d1 = {d.x, d.y - u};
	
	// draw_line(img, a, a1, color);
	draw_line(img, b, b1, color);
	draw_line(img, c, c1, color);
	draw_line(img, d, d1, color);

	draw_square(img, a1, b1, c1, d1, color);
}

void	iso_test(t_minimap *mini)
{
	// int			margin = 50;
	int			width = mini->img->width;
	int			height =  mini->img->height;
	int			half_width = width / 2;
	int			half_height = height / 2;
	t_fpoint	center = {half_width, half_height};

	
	draw_background(mini->img, HEX_BLACK);
	// draw_line(mini->img, (t_fpoint){margin, half_height}, (t_fpoint){width - margin, half_height}, HEX_BLUE); // horizontal
	// draw_line(mini->img, (t_fpoint){half_width, margin}, (t_fpoint){half_width, height - margin}, HEX_ORANGE); // vertical

	iso_tile(mini->img, center, mini->tile_size, half_width, HEX_GREEN);
	// iso_cube_seethrough(mini->img, center, mini->tile_size, half_width, HEX_GREEN);
	// iso_cube_opaque(mini->img, center, mini->tile_size, half_width, HEX_GREEN);
}

/* ************************************************************************** */
/* ************************************************************************** */

void	iso_grid(t_minimap *mini)
{
	t_fpoint	tile;
	int	x;
	int	y;
	
	// mini->tile_size = adjust_tile_size(mini->img, map);
	mini->tile_size = ft_min(mini->img->width / 10, mini->img->height / 10);
	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			tile.x = x * mini->tile_size;
			tile.y = y * mini->tile_size;
			// if (x >= 0 && x < map->width && y >= 0 && y < map->height)
			if ((x % 4 == 0 && y == 0) || x == 9) //random test
				iso_cube_opaque(mini->img, tile, mini->tile_size, WIDTH / 2, HEX_ORANGE);
				// iso_cube_seethrough(mini->img, tile, mini->tile_size, WIDTH / 2, HEX_GREEN);
			else
				iso_tile(mini->img, tile, mini->tile_size, WIDTH / 2, HEX_PURPLE);
			x++;
		}
		y++;
	}
}
