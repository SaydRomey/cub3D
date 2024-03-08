/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:15:08 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/07 22:01:24 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	proof(char *str)
{
	char	*color = ORANGE;

	ft_printf("\n%s*->%s", color, RESET);
	ft_printf("%s", str);
	ft_printf("%s<-*%s\n", color, RESET);
}

/* ************************************************************************** */

void	test_scene(t_scene scene)
{
	ft_printf("\nTesting scene\n");
	// 
	proof("Texture paths");
	ft_printf("North: %s\n", scene.wall_textures[NO]);
	ft_printf("South: %s\n", scene.wall_textures[SO]);
	ft_printf("East: %s\n", scene.wall_textures[EA]);
	ft_printf("West: %s\n", scene.wall_textures[WE]);
	// 
	proof("Floor colors");
	ft_printf("RED:   %s\n", scene.colors[FLOOR][R]);
	ft_printf("GREEN: %s\n", scene.colors[FLOOR][G]);
	ft_printf("BLUE:  %s\n", scene.colors[FLOOR][B]);
	ft_printf("Hexa value: %X\n", get_color(&scene, FLOOR));
	// 
	proof("Ceiling colors");
	ft_printf("RED:   %s\n", scene.colors[CEILING][R]);
	ft_printf("GREEN: %s\n", scene.colors[CEILING][G]);
	ft_printf("BLUE:  %s\n", scene.colors[CEILING][B]);
	ft_printf("Hexa value: %X\n", get_color(&scene, CEILING));
	// 
	proof("Map section");
	t_list	*tmp = scene.map_list;
	while (tmp)
	{
		ft_printf("%s$\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_printf("longest line length -> %d\n", get_map_width(scene.map_list));
	ft_printf("number of nodes -> %d\n", ft_lstsize(scene.map_list));
	ft_printf("Starting orientation -> %c\n", scene.spawn_orientation);
	// 
	ft_printf("Starting player position -> x%d, y%d\n", \
	scene.starting_position.x, scene.starting_position.y); //?missing
}

/* ************************************************************************** */

# define GRAY "\033[90m"

static void	color_print(char *str, char *color)
{
	printf("%s%s%s", color, str, RESET);
}

static void fancy_print(int value)
{
	if (value == 0)
		color_print("[]", GREEN);
	if (value == 1)
		color_print("██", ORANGE);
	if (value == -1)
		color_print("[]", GRAY);
	if (value == -2)
		color_print("██", GRAY);
}

void	print_raw_array(int **array, int height, int width)
{
	int	i = 0;

	while (i < height)
	{
		printf("row %2d-> ", i);
		int	j = 0;
		while (j < width)
		{
			printf("%2d ", array[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

void	print_2d_array(int **array, int height, int width)
{
	int	i = 0;

	while (i < height)
	{
		printf("row %2d-> ", i);
		int	j = 0;
		while (j < width)
		{
			fancy_print(array[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}



void	test_map(t_map map)
{
	ft_printf("\nTesting map\n");
	// 
	proof("Dimensions");
	ft_printf("map height: %d\n", map.height);
	ft_printf("map width: %d\n", map.width);
	// 
	proof("Raw values");
	print_raw_array(map.map_array, map.height, map.width);
	proof("Color representation");
	print_2d_array(map.map_array, map.height, map.width);
	// 
	proof("Colors");
	ft_printf("Floor:   %X\n", map.floor_color);
	ft_printf("Ceiling: %X\n", map.ceiling_color);
	// 
	// test for the images?
	// test for position and orientation ?
}
/* ************************************************************************** */

void	test_term_colors(void)
{
	int		i;
	int		j;
	int		code;

	i = 0;
	while (i < 16)
	{
		j = 0;
		while (j < 16)
		{
			code = i * 16 + j;
			printf("\033[38;5;%dm %4d", code, code);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\033[0m\n");
}

/* ************************************************************************** */
/* ************************************************************************** */
