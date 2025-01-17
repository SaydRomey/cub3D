/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:15:08 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/24 15:06:36 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* tmp to display debug messages
*/
// # define PRINT_PROOF		0
# define PRINT_PROOF		1

void	proof(char *str)
{
	char	*color = ORANGE;

	if (PRINT_PROOF)
	{
		ft_printf("\n%s*->%s", color, RESET);
		ft_printf("%s", str);
		ft_printf("%s<-*%s\n", color, RESET);
	}
}

void	cproof(char *str, char *color)
{
	if (PRINT_PROOF)
	{
		ft_printf("\n%s*->%s", color, RESET);
		ft_printf("%s", str);
		ft_printf("%s<-*%s\n", color, RESET);
	}
}

void	vaproof(char *str, ...)
{
	char	*color = ORANGE;
	va_list	args;

	va_start(args, str);
	if (PRINT_PROOF)
	{
		ft_printf("\n%s*->%s", color, RESET);
		ft_vprintf(str, args);
		ft_printf("%s<-*%s\n", color, RESET);
	}
	va_end(args);
}


/* ************************************************************************** */

void	test_scene(t_scene scene)
{
	ft_strainbow("\n----- Testing scene -----", 1);
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
	ft_printf("Hexa:  %X\n", get_color(&scene, FLOOR));
	// 
	proof("Ceiling colors");
	ft_printf("RED:   %s\n", scene.colors[CEILING][R]);
	ft_printf("GREEN: %s\n", scene.colors[CEILING][G]);
	ft_printf("BLUE:  %s\n", scene.colors[CEILING][B]);
	ft_printf("Hexa:  %X\n", get_color(&scene, CEILING));
	// 
	proof("Map section");
	t_list	*tmp = scene.map_list;
	while (tmp)
	{
		ft_printf("%s$\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_printf("\n");
	ft_printf("longest line length   -> %d\n", get_map_width(scene.map_list));
	ft_printf("number of nodes       -> %d\n", ft_lstsize(scene.map_list));
	ft_printf("Starting orientation  -> %c\n", scene.spawn_orientation);
	// 
	printf("Starting position     -> x[%d], y[%d]\n", \
	(int)scene.starting_position.x, (int)scene.starting_position.y);
}

/* ************************************************************************** */

# define GRAY "\033[90m" //put in libft_utils.h

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
	if (value == 2)
		color_print("██", YELLOW);
	if (value == 3)
		color_print("██", BLUE);
	if (value == -1)
		color_print("[]", GRAY);
	if (value == -2)
		color_print("██", GRAY);
}

static void	print_raw_array(int **array, int height, int width)
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

static void	print_2d_array(int **array, int height, int width)
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
	ft_strainbow("\n----- Testing map -----", 1);
	// 
	proof("Dimensions");
	ft_printf("map height: %d\n", map.height);
	ft_printf("map width:  %d\n", map.width);
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

	proof("Spawn");
	ft_printf("orientation: %c\n", map.spawn_orientation);
	printf("position:    X[%f], Y[%f]\n", map.starting_position.x, map.starting_position.y);
}

/* ************************************************************************** */

void	test_player(t_player player)
{
	ft_strainbow("\n----- Testing player -----", 1);
	// 
	printf("position:  x%f, y%f\n", player.position.x, player.position.y);
	printf("angle:      %f\n", player.angle);
	printf("fov:        %f\n", player.fov);
	printf("delta:      x%f, y%f\n", player.delta.x, player.delta.y);
	printf("cam_plane:  x%f, y%f\n", player.cam_plane.x, player.cam_plane.y);
	printf("speed:      %f\n", player.speed);
	printf("turn speed: %f\n", player.turn_speed);
}
