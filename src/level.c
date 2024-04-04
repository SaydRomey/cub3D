/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:21:17 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/04 18:43:40 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
when changing level !!

update the window title
update cub.current_level

redraw the minimap


*/

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
		// might need to deep copy the textures also ?
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
	
	node = ft_lstnew(new_level);
	if (!node)
	{
		delete_level(new_level);
		return ; //malloc error
	}
	ft_lstadd_back(levels, node);
}

// void	add_new_level(t_list **levels, t_scene scene, char *filepath)
// {
// 	t_level	*new_level;
// 	t_list	*node;

// 	new_level = (t_level *)malloc(sizeof(t_level));
// 	if (!new_level)
// 		return ; //malloc error
	
// 	new_level->filepath = filepath; //for changing the title later
// 	new_level->index = ft_lstsize(*levels);
// 	new_level->map = init_map(&scene);
// 	validate_map(&new_level->map);
		
// 	node = ft_lstnew(new_level);
// 	if (!node)
// 	{
// 		delete_level(new_level);
// 		return ; //malloc error
// 	}
// 	ft_lstadd_back(levels, node);
// }

void	delete_level(void *level)
{
	t_level	*lvl;
	
	lvl = (t_level *)level;
	if (lvl)
	{
		cleanup_map(&lvl->map); //and further specific cleaning if needed
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

t_level	*get_level(t_list *levels, int index)
{
	t_list	*node;
	t_level	*lvl;

	node = ft_lstget(levels, index);
	if (node == NULL)
	{
		// handle index out of bounds
		return (NULL);
	}
	lvl = (t_level *)node->content;
	if (!lvl)
	{
		return (NULL);
	}
	return (lvl);
}

t_map	*get_map(t_list *levels, int index)
{
	t_list	*node;
	t_level	*lvl;

	node = ft_lstget(levels, index);
	if (node == NULL)
	{
		// handle index out of bounds
		return (NULL);
	}
	lvl = (t_level *)node->content;
	if (!lvl)
	{
		return (NULL);
	}
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
