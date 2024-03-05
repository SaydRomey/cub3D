/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:30:33 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/05 17:59:40 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*

bool check_vertical_isolation(int **map, int width, int height) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (map[y][x] == 0) {
                // Check above unless at the top row
                if (y > 0 && (map[y - 1][x] != 1 && map[y - 1][x] != -1)) {
                    return false;
                }
                // Check below unless at the bottom row
                if (y < height - 1 && (map[y + 1][x] != 1 && map[y + 1][x] != -1)) {
                    return false;
                }
            }
        }
    }
    return true;
}


bool check_vertical_isolation(int **map, int width, int height) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            // Check if the current element is '0'
            if (map[y][x] == 0) {
                // Check the element above unless we're at the top row
                if (y > 0 && (map[y - 1][x] != 1 || map[y - 1][x] == -1)) {
                    return false; // Invalid if above is not '1' or is a space
                }
                // Check the element below unless we're at the bottom row
                if (y < height - 1 && (map[y + 1][x] != 1 || map[y + 1][x] == -1)) {
                    return false; // Invalid if below is not '1' or is a space
                }
            }
        }
    }
    return true; // The map is valid if no '0' is improperly isolated
}

*/

// void	store_map_line(t_list **map_list, char *line)
// {
// 	t_list	*node;

// 	node = ft_lstnew(ft_strtrim(line, "\n"));
// 	if (!node)
// 		return ; //malloc error
// 	ft_lstadd_back(map_list, node);
// }

void	store_map_line(t_list **map_list, char *line)
{
	t_list	*node;
	char	*copy;
	char	*last_one;
	char	*trimmed;
	size_t	new_len;

	copy = ft_strdup(line);
	if (!copy)
		return ; //malloc error
	last_one = ft_strrchr(copy, '1');
	if (last_one != NULL)
	{
		new_len = last_one - copy + 1; // calculate length from start to the last '1'
		trimmed = ft_substr(copy, 0, new_len);
		if (!trimmed)
		{
			free(copy);
			return ; //malloc error
		}
		free(copy);
	}
	else
		trimmed = copy;
	node = ft_lstnew(trimmed);
	if (!node)
	{
		free(copy);
		return ; //malloc error
	}
	ft_lstadd_back(map_list, node);
}

int	get_map_width(t_list *map_list)
{
	int	max_width;
	int	current_length;

	max_width = 0;
	while (map_list)
	{
		current_length = ft_strlen((char *)map_list->content);
		if (current_length > max_width)
			max_width = current_length;
		map_list = map_list->next;
	}
	return (max_width);
}

void	free_map(int **map, int height)
{
	int	i;

	if (!map)
		return;
	i = 0;
	while (i < height)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

static int **allocate_grid(int height, int width)
{
	int	**grid;
	int	i;
	
	// grid = (int **)ft_calloc(height, sizeof(int *));
	grid = (int **)malloc(sizeof(int *) * height);
	if (!grid)
		return (NULL);
	
	i = 0;
	while (i < height)
	{
		grid[i] = (int *)ft_calloc(width, sizeof(int));
		// grid[i] = (int *)malloc(sizeof(int) * width);
		if (!grid[i])
		{
			while (--i >= 0)
				free(grid[i]);
			free(grid);
			return (NULL);
		}
		// ft_memset(map[i], 2, width * sizeof(int));
		// ?
		int	j = 0;
		while (j < width)
		{
			grid[i][j] = -2;
			j++;
		}
		i++;
	}
	return (grid);
}

static int	char_to_int(char c) //change this later
{
	if (c == ' ')
		return (-1);
	else if (c == '1')
		return (1);
	else if (c == '0')
		return (0);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	else
		return (-2); //tmp, should not get here?
}

int		**get_2d_map(t_list *map_list, int height, int width)
{
	int		**map_array;
	int		row;
	int		col;
	char	*line;
	// int		value;
	
	// map_array = allocate_map(ft_lstsize(map_list), get_map_width(map_list));
	map_array = allocate_grid(height, width);
	if (!map_array)
		return (NULL);
	
	row = 0;
	while (map_list) // && row < height)
	{
		line = (char *)map_list->content;
		col = 0;
		while (col < width && line[col])
		{
			map_array[row][col] = char_to_int(line[col]);
			col++;
		}
		map_list = map_list->next;
		row++;
	}
	return (map_array);
}

// int	**get_2d_map(t_list *map_list, int height, int width, t_point *start_position)
// {
// 	int		**map;
// 	int		row;
// 	int		col;
// 	char	*line;
// 	(void)start_position;

// 	map = allocate_map(height, width);
// 	if (!map)
// 		return (NULL);
// 	row = 0;
// 	while (row < height && map_list)
// 	{
// 		line = (char *)map_list->content;
// 		col = 0;
// 		while (col < width && line[col])
// 		{
// 			int	value = char_to_int(line[col]);

// 			if (ft_strchr("NSEW", line[col]))
// 			{
// 				printf("Start x = %d\n", col);
// 				printf("Start y = %d\n", row);
// 			}
// 			map[row][col] = value;
// 			// printf("[%2d, %2d] ",col, row);
// 			// printf("[%c] ", line[col]);
// 			// printf("[%2d] ", value);
// 			col++;
// 		}
// 		// printf("\n");
// 		row++;
// 		map_list = map_list->next;
// 	}
// 	// printf("\n");
// 	return (map);
// }


// int	**get_2d_map(t_list *map_list, int height, int width, t_point *start_position)
// {
// 	int		**map;
// 	int		row;
// 	int		col;
// 	char	*line;

// 	map = allocate_map(height, width);
// 	if (!map)
// 		return (NULL);
// 	row = 0;
// 	while (row < height && map_list)
// 	{
// 		line = (char *)map_list->content;
// 		col = 0;
// 		while (col < width && line[col])
// 		{
// 			int	value = char_to_int(line[col]);
// 			if (value == -2)
// 			{
// 				free_map(map, height);
// 				return (NULL);
// 			}
// 			if (ft_strchr("NSEW", line[col]))
// 			{
// 				start_position->x = col;
// 				start_position->y = row;
// 			}
// 			map[row][col] = value;
// 			col++;
// 		}
// 		row++;
// 		map_list = map_list->next;
// 	}
// 	return (map);
// }


// void	store_map_line(t_list **map_list, char *line)
// {
// 	t_list	*node;
// 	char	*copy;
// 	size_t	len;

// 	copy = ft_strdup(line);
// 	if (!copy)
// 		return ; //malloc error
// 	len = ft_strlen(copy);
// 	if (len > 0 && copy[len - 1] == '\n')
// 		copy[len - 1] = '\0';
// 	node = ft_lstnew(copy);
// 	if (!node)
// 	{
// 		free(copy);
// 		return ; //malloc error
// 	}
// 	ft_lstadd_back(map_list, node);
// }
