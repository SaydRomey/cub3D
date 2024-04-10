/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:21:17 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/10 16:21:39 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
TODO:
a 'next_lvl() prev_lvl()' that block at 0 and ft_lstsize - 1 ?

set the t_player's position and orientation when changing levels *!!
*/

// void	init_first_level();

void	change_level(int index) //test with the minimap and window title only
{
	t_cub	*cub;
	t_level	*lvl;
	t_level	*next_lvl;

	cub = call_cub();
	if (cub->current_level == index)
		return;
	
	// setup next level
	next_lvl = get_level(index);
	if (next_lvl)
	{
		// close current level stuff...
		lvl = get_level(cub->current_level);
		lvl->mini.img->instances->enabled = false;
		
		change_window_title(next_lvl->filepath);
		draw_minimap(&next_lvl->mini, &next_lvl->map);
		cub->current_level = index;

		// player adjustment (change to fit elevator logic instead later...)
		cub->player = init_player(&next_lvl->map); //test
	}
	return;
}

/* ************************************************************************** */
/* ************************************************************************** */

/* **separate this in helper functions
*/
t_map	deep_copy_map(t_map original)
{
	mlx_t	*mlx;
	t_map	copy;
	int		i;

	mlx = call_cub()->mlx;
	copy = original; //this copies the simple fields like height, width, etc.
	
	if (original.map_array != NULL) //deep copy of map_array
	{
		copy.map_array = allocate_grid(original.height, original.width);
		if (copy.map_array != NULL)
		{
			i = 0;
			while (i < original.height)
			{
				ft_memcpy(copy.map_array[i], original.map_array[i], original.width * sizeof(int));
				i++;
			}
		}
	}
	i = 0;
	while (i < WALL_TEXTURE_LEN)
	{
		copy.wall_textures_img[i] = copy_img(original.wall_textures_img[i], mlx);
		i++;
	}
	i = 0;
	while (i < COLOR_TYPE_LEN)
	{
		copy.floor_ceiling_img[i] = copy_img(original.floor_ceiling_img[i], mlx);
		i++;
	}
	return (copy);
}

void	add_new_level(t_list **levels, t_map map, char *filepath)
{
	t_level	*new_level;
	t_list	*node;

	new_level = (t_level *)malloc(sizeof(t_level));
	if (!new_level)
		return ; //malloc error
	
	new_level->filepath = filepath;
	new_level->index = ft_lstsize(*levels);
	new_level->map = deep_copy_map(map);
	new_level->mini = init_minimap(&map);

	node = ft_lstnew(new_level);
	if (!node)
	{
		delete_level(new_level);
		return ; //malloc error
	}
	ft_lstadd_back(levels, node);

	if (new_level->index == 0)
		draw_minimap(&new_level->mini, &new_level->map); //maybe put this elsewhere.. ?
}

void	delete_level(void *level)
{
	t_level	*lvl;
	
	lvl = (t_level *)level;
	if (lvl)
	{
		cleanup_map(&lvl->map);
		mlx_delete_image(call_cub()->mlx, lvl->mini.img);
		
		free(lvl);
		proof("deleted a level");
	}
}

/* ************************************************************************** */
/* ************************************************************************** */

t_level *get_level(int index)
{
	t_list	*node;
	t_level	*lvl;

	node = ft_lstget(call_cub()->levels, index);
	if (!node)
		return (NULL);
	lvl = (t_level *)node->content;
	if (!lvl)
		return (NULL);
	return (lvl);
}

t_map	*get_map(int index)
{
	t_list	*node;
	t_level	*lvl;
	
	node = ft_lstget(call_cub()->levels, index);
	if (!node)
		return (NULL);
	lvl = (t_level *)node->content;
	if (!lvl)
		return (NULL);
	return (&(lvl->map));
}
