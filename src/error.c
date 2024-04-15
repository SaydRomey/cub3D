/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:44:01 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/15 13:33:20 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_error(char *str)
{
	t_info	*info;

	info = call_info();
	if (info->error_msg != NULL)
	{
		free(info->error_msg);
		info->error_msg = NULL;
	}
	info->error_msg = ft_strdup(str);
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
	if (!info->error_msg)
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
	ft_putstr_fd("Error\n", STDERR);
	ft_fprintf(STDERR, "%s%s%s\n", RED, get_error(), RESET);
	free_info();
	exit(FAILURE);
}

/*
error function used during the 'get_next_line()' loop
*/
void	parsing_error(char *line, int fd, t_scene *scene)
{
	if (line)
		free(line);
	close(fd);
	cleanup_scene(scene);
	error();
}

/*
mlx specific error function, uses 'mlx_errno' to identify error

	** make sure this also frees other mlx allocated ressources
	(like current images of t_cub when in init_elevator, etc.)

	// set_error((char *)mlx_strerror(mlx_errno));

*/
void	error_mlx(void)
{
	const char	*mlx_error_msg;
	
	mlx_error_msg = mlx_strerror(mlx_errno);
	set_error((char *)mlx_error_msg);
	error();
}

/*

// const char* mlx_strerror(mlx_errno_t val);

The error codes used to identify the correct error message.

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
