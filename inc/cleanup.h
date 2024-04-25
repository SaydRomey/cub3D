/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:05:40 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/24 19:15:12 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include "parsing.h"
# include "map.h"
# include "elevator.h"

// cleanup.c
void	free_map_array(int **map_array, int height); //tmp?

void	cleanup(void *param);
void	cleanup_scene(t_scene *scene);
void	cleanup_map(t_map *map);
void	cleanup_elevator(t_elevator *elevator);

#endif // CLEANUP_H
