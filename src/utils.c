/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:39:37 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/18 17:02:26 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cardinal_to_radian(char cardinal)
{
	if (cardinal == 'N')
		return (90);
	if (cardinal == 'S')
		return (270);
	if (cardinal == 'E')
		return (0);
	if (cardinal == 'W')
		return (180);
	return (-1);
}

/*
if 'value_to_find' is found in 'map->map_array',
will set the column and row in 'point_ptr' and return true
else will return false
*/
bool	find_value_in_array(t_map *map, int value_to_find, t_point *point_ptr)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map_array[y][x] == value_to_find)
			{
				*point_ptr = (t_point){x, y};
				return (true);
			}
			x++;
		}
		y++;
	}
	return (false);
}

void	toggle(bool *choice)
{
	if (*choice == ON)
		*choice = OFF;
	else
		*choice = ON;
}

void	change_window_title(char *filepath)
{
	char	*title;

	title = ft_strjoin("cub3D - ", filepath);
	mlx_set_window_title(call_cub()->mlx, title);
	free(title);
}

bool	player_is_in_elevator(t_player *player)
{
	t_level	*lvl;

	lvl = get_level(call_cub()->current_level);
	if (lvl)
	{
		if (lvl->elevator_position.x == (int)player->position.x && \
			lvl->elevator_position.y == (int)player->position.y)
			return (true);
	}
	return (false);
}
