/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segworld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/24 20:14:24 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

// void	call_segworld(t_cub *cub, t_elevator *e, t_fpoint pos, int ori)
// {
// 	int	map[8][8] = 
// 	{
// 		{1, 1, 1, 1, 1, 1, 1, 1},
// 		{1, 0, 1, 3, 1, 0, 0, 1},
// 		{1, 0, 0, 0, 1, 1, 0, 1},
// 		{1, 0, 1, 0, 0, 0, 0, 1},
// 		{1, 0, 1, 1, 1, 1, 0, 1},
// 		{1, 0, 0, 1, 0, 0, 0, 1},
// 		{1, 1, 0, 0, 0, 1, 0, 1},
// 		{1, 1, 1, 1, 1, 1, 1, 1}
// 	};
// 	int	x;
// 	int	y;
	
// 	y = 0;
// 	cub->map.width = 8;
// 	cub->map.height = 8;
// 	cub->map.floor_color = 0x00;
// 	cub->map.ceiling_color = 0x00;
// 	cub->map.wall_textures_img[NO] = load_png("img/checker.png", cub->mlx);
// 	cub->map.wall_textures_img[SO] = load_png("img/paint.png", cub->mlx);
// 	cub->map.wall_textures_img[EA] = load_png("img/pokeball.png", cub->mlx);
// 	cub->map.wall_textures_img[WE] = load_png("img/tree_trunk.png", cub->mlx);
// 	free_matrix(cub->map.map_array);
// 	cub->map.map_array = ft_calloc(cub->map.height, sizeof (int *));
// 	if (!cub->map.map_array)
// 		printf ("Malloc error\n");
// 	while (y < cub->map.height)
// 	{
// 		x = 0;
// 		cub->map.map_array[y] = ft_calloc(cub->map.width, sizeof (int));
// 		if (!cub->map.map_array[y])
// 			printf ("Malloc error\n");
// 		while (x < cub->map.width)
// 		{
// 			cub->map.map_array[y][x] = map[y][x];
// 			x++;
// 		}
// 		y++;
// 	}
// 	parse_elevator(&cub->map, e);
// 	e->id = -1;
// 	update_elevator_struct(cub, *e);
// 	change_character_coordinates(cub, pos, ori);
// }

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
	// map.floor_color = HEX_DGRAY;
	// map.ceiling_color = HEX_GRAY;
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

// t_level *call_segworld(void)
// {
// 	static t_level	segworld;

// 	if (segworld.index == 0)
// 	{
// 		segworld.filepath = "segworld";
// 		segworld.index = -1;
// 		segworld.elevator_exists = 1;
// 		segworld.elevator_position = (t_point){1, 1};
// 		segworld.elevator_orientation = cardinal_to_radian('N');
// 		segworld.map = set_segworld_map();
// 		set_segworld_elevator(&segworld, segworld.elevator_position);
// 		segworld.mini = init_minimap(&segworld.map);
// 	}
// 	return (&segworld);
// }
