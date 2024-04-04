/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:01:15 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/04 17:41:22 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_info	*call_info(void)
{
	static t_info	*info;

	if (info == NULL)
	{
		info = ft_calloc(1, sizeof(*info));
		if (!info)
			return (NULL);
	}
	return (info);
}

void	free_info(void)
{
	t_info	*info;
	
	info = call_info();
	if (info->error_msg)
	{
		free(info->error_msg);
	}
	free(info);
}

bool	there_is_a_problem(void)
{
	return (call_info()->problem);
}

void	reset_info(void)
{	
	t_info	*info;

	info = call_info();
	// ft_bzero(info, sizeof(*info));
	
	ft_bzero(info->wall_check, sizeof(bool) * WALL_TEXTURE_LEN);
	ft_bzero(info->color_check, sizeof(bool) * COLOR_TYPE_LEN);
	info->found_direction = false;
	
	proof("reset info");
}
