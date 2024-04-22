/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:14:18 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/22 17:08:39 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	valid_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension)
		set_error("Missing extension");
	else if (ft_strncmp(extension, ".cub", 5) != SAME)
		set_error("Invalid file extension");
	return (!there_is_a_problem());
}

void	validate_arguments(int argc, char **argv)
{
	int		check;
	int		i;

	if (!BONUS && argc != 2)
		va_exit_error("Usage: %s <filename>.cub", argv[0]);
	else if (BONUS && argc < 2)
		va_exit_error("Usage: %s <filename1>.cub <filename2>.cub ...", argv[0]);
	i = 1;
	while (i < argc)
	{
		if (valid_extension(argv[i]))
		{
			check = read_check(argv[i]);
			if (check == 0)
				set_error_arg("File is empty", argv[i]);
			else if (check == -1)
				set_error_arg("Could not open or read", argv[i]);
		}
		if (there_is_a_problem())
			error();
		i++;
	}
}
