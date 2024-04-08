/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:21:17 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/08 15:17:48 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
TODO:
a 'next_lvl() prev_lvl()' that block at 0 and ft_lstsize - 1 ?

set the t_player's position and orientation when changing levels *!!
*/

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

mlx_image_t	*deep_copy_image(mlx_image_t *src)
{
	mlx_image_t *copy;
	
	if (!src)
		return (NULL);
	
	copy = mlx_new_image(call_cub()->mlx, src->width, src->height);
	if (!copy)
		return (NULL);
	
	ft_memcpy(copy->pixels, src->pixels, src->width * src->height * sizeof(int));
	
	return (copy);
}


t_map	deep_copy_map(t_map original)
{
	t_map	copy;
	int		i;

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
		copy.wall_textures_img[i] = deep_copy_image(original.wall_textures_img[i]);
		i++;
	}
	i = 0;
	while (i < COLOR_TYPE_LEN)
	{
		copy.floor_ceiling_img[i] = deep_copy_image(original.floor_ceiling_img[i]);
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

t_list	*ft_lstget(t_list *lst, int index) //this will go in libft
{
	t_list	*tmp;
	int		i;

	tmp = lst;
	i = 0;
	if (index < 0)
		return (NULL);
	while (tmp != NULL && i < index)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

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

/* ************************************************************************** */

// to test when the structure is set

/*
get a specific 't_level' element using stddef.h's offsetof macro
*/
void	*get_level_element(t_list *levels, int index, size_t offset)
{
	t_list	*node;
	t_level	*lvl;
	void	*element_ptr = NULL;

	node = ft_lstget(levels, index);
	if (!node)
		return (NULL);
	
	lvl = (t_level *)node->content;
	if (!lvl)
		return (NULL);

	element_ptr = (void *)((char *)lvl + offset);

	return (element_ptr);
}

t_map	*get_map2(t_list *levels, int index) //this is an example function to understand 'offsetof'...
{
	t_map	*map_ptr;
	size_t	map_offset;

	map_offset = offsetof(t_level, map);
	
	map_ptr = (t_map *)get_level_element(levels, index, map_offset);
	if (!map_ptr)
		return (NULL);
	return (map_ptr);
}
