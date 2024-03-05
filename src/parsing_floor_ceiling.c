/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_floor_ceiling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:55:03 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/04 18:57:58 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
use itoa to validate color channel range in parsing directly?

*/

/*
need to add check for 'split[RGB_LEN + 1]' (must be NULL)
*/
static void	split_rgb(int id, char *line, t_scene *scene)
{
	char	**split;
	int		i;

	split = ft_split(line + 2, ',');
	i = 0;
	while (i < RGB_LEN)
	{
		if (split[i] == NULL)
		{
			set_error("Missing color component");
			break;
		}
		scene->colors[id][i] = ft_strtrim(split[i], " ");
		i++;
	}
	call_info()->color_check[id] = true;
	free_split(split);
}

void	parse_floor_ceiling(char *cubline, t_scene *scene)
{
	char	*colors[2];
	char	*line;
	int		id;

	colors[0] = "F ";
	colors[1] = "C ";
	line = ft_strtrim(cubline, " \t\n");
	id = 0;
	while (id < COLOR_TYPE_LEN)
	{
		if (ft_strncmp(line, colors[id], 2) == SAME)
		{
			if (call_info()->color_check[id])
			{
				set_error("Duplicate floor/ceiling color definition");
				break;
			}
			split_rgb(id, line, scene);
		}
		id++;
	}
	free(line);
	return;
}

