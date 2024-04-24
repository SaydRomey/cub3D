/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segworld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/24 00:36:28 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_segworld_elevator(t_level *segworld, t_point pos)
{
	segworld->map.map_array[pos.y][pos.x] = 3;
	if (segworld->elevator_orientation == 90)
	{
		segworld->map.map_array[pos.y][pos.x - 1] = 1;
		segworld->map.map_array[pos.y][pos.x + 1] = 1;
		segworld->map.map_array[pos.y - 1][pos.x] = 1;
	}
	else if (segworld->elevator_orientation == 270)
	{
		segworld->map.map_array[pos.y][pos.x - 1] = 1;
		segworld->map.map_array[pos.y][pos.x + 1] = 1;
		segworld->map.map_array[pos.y + 1][pos.x] = 1;
	}
	else if (segworld->elevator_orientation == 0)
	{
		segworld->map.map_array[pos.y + 1][pos.x] = 1;
		segworld->map.map_array[pos.y - 1][pos.x] = 1;
		segworld->map.map_array[pos.y][pos.x + 1] = 1;
	}
	else if (segworld->elevator_orientation == 180)
	{
		segworld->map.map_array[pos.y + 1][pos.x] = 1;
		segworld->map.map_array[pos.y - 1][pos.x] = 1;
		segworld->map.map_array[pos.y][pos.x - 1] = 1;
	}
}

static int	set_segworld_map_char(int height, int width, int x, int y)
{
	if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
		return (1);
	return (0);
}

static int	**fill_segworld_map(int height, int width)
{
	int	**map_array;
	int	x;
	int	y;

	map_array = ft_calloc(height, sizeof (int *));
	if (!map_array)
		return (NULL);
	y = 0;
	while (y < height)
	{
		map_array[y] = ft_calloc(width, sizeof (int));
		if (!map_array[y])
		{
			free_matrix(map_array);
			return (NULL);
		}
		x = 0;
		while (x < width)
		{
			map_array[y][x] = set_segworld_map_char(height, width, x, y);
			x++;
		}
		y++;
	}
	return (map_array);
}

static t_map	set_segworld_map(void)
{
	t_map	map;
	mlx_t	*mlx;

	mlx = call_cub()->mlx;
	ft_memset(&map, 0, sizeof (t_map));
	map.height = 8;
	map.width = 8;
	map.map_array = fill_segworld_map(map.height, map.width);
	map.floor_color = HEX_GROUND;
	map.ceiling_color = HEX_SKY;
	map.wall_textures_img[NO] = load_png("img/checker.png", mlx);
	map.wall_textures_img[SO] = load_png("img/paint.png", mlx);
	map.wall_textures_img[EA] = load_png("img/pokeball.png", mlx);
	map.wall_textures_img[WE] = load_png("img/tree_trunk.png", mlx);
	return (map);
}

void replace_with_segworld(t_level *next_lvl)
{
	next_lvl->filepath = "segworld";
	next_lvl->elevator_exists = 1;
	next_lvl->elevator_position = (t_point){1, 1};
	next_lvl->elevator_orientation = cardinal_to_radian('N');
	// free_matrix(next_lvl->map.map_array);
	next_lvl->map = set_segworld_map();
	set_segworld_elevator(next_lvl, next_lvl->elevator_position);
	next_lvl->mini = init_minimap(&next_lvl->map);
	next_lvl->is_segworld = true;
	next_lvl->assets = init_assets("img/flames.png", next_lvl, 8);
}
