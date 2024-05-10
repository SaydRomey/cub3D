/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segworld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:24:06 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/09 20:29:46 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
void	add_segworld(t_list **levels)
{
	t_level	*seg_lvl;
	t_list	*node;

	seg_lvl = (t_level *)ft_calloc(1, sizeof(t_level));
	if (seg_lvl)
	{
		// seg_lvl->...
	}
	else
		set_error("Malloc error");
	if (!there_is_a_problem())
	{
		node = ft_lstnew(seg_lvl);
		if (!node)
		{
			delete_level(seg_lvl);
			set_error("Malloc error");
		}
		else
			ft_lstadd_back(levels, node);
	}
	else
		error();
}
*/

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

static void	fill_segworld_array(t_map *map)
{
	int	x;
	int	y;

	if (map->map_array)
	{
		y = 0;
		while (y < map->height)
		{
			x = 0;
			while (x < map->width)
			{
				if (y == 0 || y == map->height - 1
					|| x == 0 || x == map->width - 1)
					map->map_array[y][x] = WALL;
				else
					map->map_array[y][x] = WALKABLE;
				x++;
			}
			y++;
		}
	}
}

static t_map	init_segworld_map(mlx_t *mlx)
{
	t_map	map;

	ft_memset(&map, 0, sizeof (t_map));
	map.height = 8;
	map.width = 8;
	map.map_array = allocate_grid(map.height, map.width);
	fill_segworld_array(&map);
	map.wall_textures_img[NO] = load_png(SW_1_PATH, mlx);
	map.wall_textures_img[SO] = load_png(SW_2_PATH, mlx);
	map.wall_textures_img[EA] = load_png(SW_3_PATH, mlx);
	map.wall_textures_img[WE] = load_png(SW_4_PATH, mlx);
	map.floor_color = SEG_FLOOR;
	map.ceiling_color = SEG_CEILING;
	return (map);
}

void	replace_with_segworld(t_level *next_lvl)
{
	t_level	*segworld;

	segworld = next_lvl;
	segworld->filepath = "segworld";
	cleanup_map(&segworld->map);
	segworld->map = init_segworld_map(call_cub()->mlx);
	segworld->mini = init_minimap(&segworld->map);
	segworld->elevator_exists = 1;
	segworld->elevator_position = (t_point){1, 2};
	segworld->elevator_orientation = cardinal_to_radian('S');
	set_segworld_elevator(segworld, segworld->elevator_position);
	segworld->is_segworld = true;
	segworld->assets = init_assets(A_FLAMES_PATH, segworld, 8);
}

bool	is_segworld(void)
{
	t_level	*lvl;

	lvl = get_level(call_cub()->current_level);
	if (lvl)
	{
		return (lvl->is_segworld);
	}
	return (false);
}
