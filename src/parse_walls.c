/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:54:24 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/18 19:33:30 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_wall_texture(char *cubline, t_scene *scene)
{
	char	*wall[4];
	char	*line;
	int		id;

	wall[0] = "NO ";
	wall[1] = "SO ";
	wall[2] = "EA ";
	wall[3] = "WE ";
	line = ft_strtrim(cubline, " \t\n");
	id = 0;
	while (id < WALL_TEXTURE_LEN)
	{
		if (ft_strncmp(line, wall[id], 3) == SAME)
		{
			printf ("ID = %i\n", id);
			if (call_info()->wall_check[id])
				set_error("Duplicate wall texture definition");
			else
			{
				scene->wall_textures[id] = ft_strdup(line + 3);
				call_info()->wall_check[id] = true;
			}
		}
		id++;
	}
	free(line);
	return;
}
