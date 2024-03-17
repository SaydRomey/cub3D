/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:13:48 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/16 20:14:07 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub	*call_cub(void)
{
	static t_cub	*cub;

	if (cub == NULL)
	{
		cub = ft_calloc(1, sizeof(*cub));
		if (!cub)
			return (NULL);
	}
	return (cub);
}

int	**call_array(void)
{
	return (call_cub()->map.map_array);
}

int	call_width(void)
{
	return (call_cub()->map.width);
}

int	call_height(void)
{
	return (call_cub()->map.height);
}
