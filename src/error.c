/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:44:01 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/22 20:15:32 by cdumais          ###   ########.fr       */
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
mlx specific error function, uses 'mlx_errno' to identify error

	** make sure this also frees other mlx allocated ressources
	(like current images of t_cub when in init_elevator, etc.)

*/
void	error_mlx(void)
{
	const char	*mlx_error_msg;

	mlx_error_msg = mlx_strerror(mlx_errno);
	set_error((char *)mlx_error_msg);
	error();
}
