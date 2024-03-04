/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/04 17:18:09 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// t_cub	init_cub(char *filepath)
// {
// 	t_cub	cub;
// 	char	*title;

// 	ft_memset(&cub, 0, sizeof(t_cub));
// 	title = ft_strjoin("cub3D - ", filepath);
// 	cub.mlx = mlx_init(WIDTH, HEIGHT, title, FALSE);
// 	free(title);
// 	if (!cub.mlx)
// 		error();
// 	return (cub);
// }

// void	setup_images(t_cub *cub)
// {
// 	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
// 	if (!cub->img)
// 		error();
// 	cub->minimap_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT); //to change later?
// 	if (!cub->minimap_img)
// 		error();
// 	// 
// 	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) < SUCCESS)
// 		error();
// 	cub->img->instances->enabled = false; //tmp
// 	if (mlx_image_to_window(cub->mlx, cub->minimap_img, 0, 0) < SUCCESS)
// 		error();
// 	// cub->minimap_img.instance.enabled = false; //tmp
// }

/*
hooks and loops
*/
// void	cub_loop(t_cub *cub)
// {
// 	mlx_key_hook(cub->mlx, &keyhooks, cub);
// 	mlx_loop_hook(cub->mlx, update, cub);
	
// 	mlx_loop(cub->mlx);
// }

/* ************************************************************************** */

/*
cub3d flow

check arguments

parse the cubfile

*(either validate cubfile during parsing,
or during the extraction of the info)*

convert the parsed info into usefull data:

wall texture paths: exists
no duplicate, all 4 a present

rgb color values are in range [0-255]
have exactly 3 values (check split[3],
should be null), no duplicate, all 2 present

map part: starts with a valid wall line (all '1' or '1' and empty spaces)
each following line starts with spaces until a 1
each line is composed of valid map chars ("10 NSEW") and not only ' '
use a char to store the starting orientation (maybe position too?) init it to '\0'
then check if not '\0', then duplicate starting char, also if still '\0' after map parsing, no starting char
map must also end with a valid wall line

//

extract the info from the t_scene, then free the t_scene (for the next room maybe?)

the wall texture paths could be converted to a usable array of images (check for proper dimensions)
or they could be textures

the rgb values should be converted to an int, usable by the function that draws
the floor image and the ceiling image
(currently we are drawing the pixels of upper half of an image, then the bottom half, to eventually draw the rays over them..)
so maybe have an floor image, a ceiling image, use memset to set the whole pixel data instead of calling the draw pixel function
(this also makes the images accessible to be textured (c'est pour toi ca oli ;) )

the map is currently a t_list where each node is a row.
it must be converted to a 2d int array

the conversion part is a bit more complex..

the height and width must be defined to malloc the int**
count nodes with ft_lstsize to get number of rows (height)
and a simple function using ft_max on each ft_strlen of the rows gives the largest number of columns (width)

*(check if space and tabs create a problem here..)

after the memory allocation, we need to get a specific int for each map chars
*(ideally, validation of map chars done in parsing)
then place that int at the corresponding position of the int **array

*(test here if the array printed is what we want)

we should retain the coordinates of the starting point as a (x, y) in the 2d array
*(ideally, the verification for uniqueness and presence of starting point done in parsing)

then use a flood fill to validate the map array:
the flood fill should start at the player position, and recursively convert the walkable space to a '0' char

the validation: !** (implement more complex checking for map that have extruding sections, a.k.a. not square or rectangular)


once all the infos are parsed, validated and extracted, we free the t_scene

////
error and leaks handling:

during arg check, if failure, close fd and exit

during parsing,
if wall texture path or rgb fails, free the currently allocated ones, then exit

if the t_list of the map portion fails, free the wall texture paths, the colors and nodes allocated up to now

if no t_list was done, free the paths and the rgb strings

** a function freeing all parsed info should be accessible during the extracting of parsed info **

during extracting info, if mlx functions fail, use the mlx_strerror, but free the t_scene before exiting

//



////

init the t_cub struct

init mlx

*/

// static void	test_parsing(t_scene scene)
// {
// 	ft_printf("\nTexture paths:\n");
// 	ft_printf("North: %s\n", scene.wall_textures[NO]);
// 	ft_printf("South: %s\n", scene.wall_textures[SO]);
// 	ft_printf("East: %s\n", scene.wall_textures[EA]);
// 	ft_printf("West: %s\n", scene.wall_textures[WE]);
// 	// 
// 	ft_printf("\nFloor and Ceiling colors:\n");
// 	ft_printf("RED:   %s\n", scene.colors[FLOOR][R]);
// 	ft_printf("GREEN: %s\n", scene.colors[FLOOR][G]);
// 	ft_printf("BLUE:  %s\n", scene.colors[FLOOR][B]);
// 	scene.floor = get_color(&scene, FLOOR);
// 	ft_printf("Hexa value: %X\n", scene.floor);

// 	ft_printf("\nCeiling colors:\n");
// 	ft_printf("RED:   %s\n", scene.colors[CEILING][R]);
// 	ft_printf("GREEN: %s\n", scene.colors[CEILING][G]);
// 	ft_printf("BLUE:  %s\n", scene.colors[CEILING][B]);
// 	scene.ceiling = get_color(&scene, CEILING);
// 	ft_printf("Hexa value: %X\n", scene.ceiling);
// }

int	main(int argc, char **argv)
{
	t_scene	scene;
	// t_cub	cub;

	validate_arguments(argc, argv);

	scene = parse_cubfile(argv[1]);

/* ************************************************************************** */
// tests
/* ************************************************************************** */
	ft_printf("\n");
	ft_printf("map width -> %d\n", get_map_width(scene.map_list));
	ft_printf("map height-> %d\n", ft_lstsize(scene.map_list));
	ft_printf("\n");
	while (scene.map_list)
	{
		ft_printf("%s$\n", (char *)scene.map_list->content);
		
		scene.map_list = scene.map_list->next;
	}
	ft_printf("\n");
	ft_printf("Starting orientation-> %c\n", scene.spawn_orientation);
/* ************************************************************************** */

		
	// &scene.next = parse_cubfile("./map/lvl2.cub");
	// validate_scene(&scene);

	// cub = init_cub(argv[1]);
	// cub.minimap = init_map(&scene);
	// cub.player = init_player((t_point){100,100}, 'S');

	// setup_images(&cub);
	
	

	// cub_loop(&cub);
	// cleanup(&cub);

	return (SUCCESS);
}

/*
	
	*/