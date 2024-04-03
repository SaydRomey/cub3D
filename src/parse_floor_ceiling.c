/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_ceiling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:55:03 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/03 12:39:25 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	color_is_invalid(char *color[RGB_LEN])
{
	int	i;
	int	value;

	i = 0;
	while (i < RGB_LEN)
	{
		value = ft_atoi(color[i]);
		if (value < 0 || value > 255)
			return (true);
		i++;
	}
	return (false);
}

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
	if (split[RGB_LEN])
		set_error("Too many colors");
	free_split(split);
	if (color_is_invalid(scene->colors[id]))
		set_error("Color value out of range (0 - 255)");
	call_info()->color_check[id] = true;
}

// void	parse_floor_ceiling_texture(char *line, t_scene *scene);
// {
// 	if (BONUS)
// 	{
		
// 	}
// }

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
	// parse_floor_ceiling_texture(line, scene);
	free(line);
	return;
}
