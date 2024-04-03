/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:21:17 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/02 22:29:48 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_new_level(t_list **levels, t_map map)
{
	t_level	*new_level;
	t_list	*node;

	new_level = (t_level *)malloc(sizeof(t_level));
	if (!new_level)
		return ; //malloc error
		
	new_level->map = map;
	new_level->index = ft_lstsize(*levels);
	
	// add other parameters later..
	
	node = ft_lstnew(new_level);
	if (!node)
	{
		free(new_level);
		return ; //malloc error
	}
	ft_lstadd_back(levels, node);
}

void	delete_level(void *level)
{
	t_level	*lvl;
	
	lvl = (t_level *)level;
	// specific cleanup here... (scene, map, etc)
	free(lvl);
	proof("deleted a level");
}
