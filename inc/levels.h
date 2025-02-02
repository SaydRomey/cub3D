/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:59:04 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/29 15:37:50 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEVELS_H
# define LEVELS_H

# include "map.h"
# include "minimap.h"
# include "utils.h"
# include "asset.h"
# include "libft.h"

typedef struct s_level
{
	char		*filepath;
	int			index;
	t_map		map;
	t_minimap	mini;
	bool		elevator_exists;
	t_point		elevator_position;
	int			elevator_orientation;
	bool		is_segworld;
	int			assets_total;
	t_asset		*assets;
}				t_level;

// level_change.c
void	change_level(int index);

// level_utils.c
t_level	*get_level(int index);
t_map	*get_map(int index);
t_map	deep_copy_map(t_map original);

// level.c
void	add_new_level(t_list **levels, t_map map, char *filepath);
void	delete_level(void *level);

#endif // LEVELS_H
