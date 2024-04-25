
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
	
	// 
	map_ptr = (t_map *)get_level_element(levels, index, map_offset);
	// 
	if (!map_ptr)
		return (NULL);
	return (map_ptr);
}
