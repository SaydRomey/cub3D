/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segworld.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:39:40 by cdumais           #+#    #+#             */
/*   Updated: 2024/05/06 18:06:01 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEGWORLD_H
# define SEGWORLD_H

# define SW_1_PATH			"img/segworld/segworld_1.png"
# define SW_2_PATH			"img/segworld/segworld_2.png"
# define SW_3_PATH			"img/segworld/segworld_3.png"
# define SW_4_PATH			"img/segworld/segworld_4.png"

# define SEG_CEILING		0x2A2A2AFF
# define SEG_FLOOR			0x424242FF

// segworld.c
void	replace_with_segworld(t_level *next_lvl);
bool	is_segworld(void);

#endif // SEGWORLD_H
