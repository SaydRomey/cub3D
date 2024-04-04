/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:15:08 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/03 19:34:45 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	proof(char *str)
{
	char	*color = ORANGE;

	if (call_info()->print_proof)
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
	if (call_info()->print_proof)
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
	ft_strainbow("\n----- Testing map -----", 1);
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

/*
test to call in mlx_loop_hook's function
*/
// void	grayscale_test(t_cub *cub)
// {
// 	if (cub->keys.up)
// 	{
// 		if (call_info()->grayscale >= 245)
// 			call_info()->grayscale = 0;
// 		else
// 			call_info()->grayscale += 5;
// 	}
// 	if (cub->keys.down)
// 	{
// 		if (call_info()->grayscale <= 10)
// 			call_info()->grayscale = 255;
// 		else
// 			call_info()->grayscale -= 5;
// 	}
// 	if (cub->keys.backspace)
// 		ft_printf("grayscale: %u\n", call_info()->grayscale);
// 	fill_img((cub->mini).img, call_info()->grayscale); // tmp test to set grayscale
// }
/* ************************************************************************** */
