/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:14:18 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/04 19:20:51 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_arguments(int argc, char **argv)
{
	char	*extension;
	int		check;

	if (argc != 2)
		va_exit_error("Usage: %s <filename>.cub", argv[0]);

	extension = ft_strrchr(argv[1], '.');
	if (!extension)
		set_error("Missing extension");
	else if (ft_strncmp(extension, ".cub", 5) != SAME)
		set_error("Invalid file extension");
	else
	{
		check = read_check(argv[1]);
		if (check == 0)
			set_error_arg("File is empty", argv[1]);
		else if (check == -1)
			set_error_arg("Could not open or read", argv[1]); 
	}
	if (there_is_a_problem())
		error();
	// ft_printf("Args valid\n"); //tmp
}
