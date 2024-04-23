/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __todo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:31:55 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/22 20:38:50 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO:

make floor ceiling raycasting an option (currently testing with '2')
*!! (check if colors are getting copied okay...)

cleanup 'pixel.c'

add 'if (BONUS)' checks for functions that are not in mandatory part:
	mouse control,
	...

**************************************************************************

Minimap:

add enable/disable controls

clamp on the edges or use margin ??**

make tests with rotating the minimap instead of the player
make tests with iso minimap

**************************************************************************
Elevator:


*ideas*
	do we implement a waiting period
	elevator music ?

	*! cue elevator music ? (should we adjust music volume with player's proximity and cut it when doors are closed ?)


**************************************************************************

TODO maybe:

add '%f' in ft_printf ? and maybe width also ?

create tutorial or instruction menu ? (mouse for clicking on elevator buttons)


**************************************************************************
Segworld:


if one of the levels does not have an elevator,
and the player tries to get to it through an elevator,
we go into segworld, and the elevator breaks... TUN TUN TUNNNNH !!!

- add flickering lights, shadow effect

- invert controls ?

- use the lerp effect with random pixel value

*/
