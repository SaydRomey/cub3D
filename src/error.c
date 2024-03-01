/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:44:01 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/01 14:39:55 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_error(char *str)
{
	t_info	*info;

	info = call_info();
	// if (info->error_msg != NULL)
	// 	free(info->error_msg);
	info->error_msg = str;
	info->problem = true;
}

void	set_error_arg(char *str, char *arg)
{
	char	*full_error;

	full_error = ft_strjoin_with(str, ": ", arg);
	// full_error = ft_strjoin(str, arg);
	if (full_error)
	{
		set_error(full_error);
		free(full_error);	
	}
}

char	*get_error(void)
{
	t_info	*info;

	info = call_info();
	if (!info->error_msg) //|| !info->problem)
		return ("[error message not set]");

	return (info->error_msg);
}

/*
as requested by the pdf:
"If any misconfiguration of any kind is encountered in the file,
the program must exit properly and return "Error\n"
followed by an explicit error message of your choice.
*/
void	error(void)
{
	char	*red_error;

	ft_putstr_fd("Error\n", STDERR);
	red_error = ft_strjoin_with(RED, get_error(), RESET);
	ft_fprintf(STDERR, "%s%s%s\n", RED, get_error(), RESET);
	// ft_putendl_fd(get_error(), STDERR);

	free_info();
	exit(FAILURE);
}

void	parse_error(char *line, int fd, t_scene *scene)
{
	int	i;

	if (line)
		free(line);
	close(fd);
	i = 0;
	while (i < WALL_TEXTURE_LEN)
	{
		if (scene->wall_textures[i])
			free(scene->wall_textures[i]);
		i++;
	}
	i = 0;
	while (i < RGB_LEN)
	{
		if (scene->colors[FLOOR][i])
			free(scene->colors[FLOOR][i]);
		if (scene->colors[CEILING][i])
			free(scene->colors[CEILING][i]);
		i++;
	}
	if (scene->map_list)
		ft_lstclear(&scene->map_list, free); //tmp, this should be handled in the map part..
	error();
}

// void	error(void)
// {
// 	ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR);
// 	exit(FAILURE);
// }


// 
// enum e_error_type
// {
// 	PARSING_ERROR,
// 	MLX_ERROR
// };

/*
test with adapt error to type
*/
// void	error(int error_type)
// {
// 	ft_putstr_fd("Error\n");
// 	if (error_type == PARSING_ERROR)
// 		ft_putendl_fd(get_error(), STDERR);
// 	if (error_type == MLX_ERROR)
// 		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR); //check format later

// 	free_info();
// 	exit(FAILURE);
// }



// possible errors : PARSING	EXTRACTING	MLX	

//= Error Functions =//

// const char* mlx_strerror(mlx_errno_t val);

// The error codes used to identify the correct error message.
/*
typedef enum mlx_errno
{
	MLX_SUCCESS = 0,	// No Errors
	MLX_INVEXT,			// File has an invalid extension
	MLX_INVFILE,		// File was invalid / does not exist.
	MLX_INVPNG,			// Something is wrong with the given PNG file.
	MLX_INVXPM,			// Something is wrong with the given XPM file.
	MLX_INVPOS,			// The specified X/Y positions are out of bounds.
	MLX_INVDIM,			// The specified W/H dimensions are out of bounds.
	MLX_INVIMG,			// The provided image is invalid, might indicate mismanagement of images.
	MLX_VERTFAIL,		// Failed to compile the vertex shader.
	MLX_FRAGFAIL,		// Failed to compile the fragment shader.
	MLX_SHDRFAIL,		// Failed to compile the shaders.
	MLX_MEMFAIL,		// Dynamic memory allocation has failed.
	MLX_GLADFAIL,		// OpenGL loader has failed.
	MLX_GLFWFAIL,		// GLFW failed to initialize.
	MLX_WINFAIL,		// Failed to create a window.
	MLX_STRTOOBIG,		// The string is too big to be drawn.
	MLX_ERRMAX,			// Error count
}	mlx_errno_t;
*/