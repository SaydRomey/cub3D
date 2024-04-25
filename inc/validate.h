/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:31:16 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/24 18:32:12 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_H
# define VALIDATE_H

# include "map.h"
# include "parsing.h"

// validate_map.c
void	validate_map(t_map *map);

// validate_scene.c
void	validate_scene(t_scene *scene);

// validate.c
void	validate_arguments(int argc, char **argv);

#endif // VALIDATE_H
