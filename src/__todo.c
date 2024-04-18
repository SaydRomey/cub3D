/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __todo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:31:55 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/18 15:59:31 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO:

**!! currently segfaults if a map has no elevator (in normal mode, did not test in bonus mode).


implement parsing and verification of elevator in parse_map()
** (make a list of what is valid, what is not, edge cases, etc..)

**************************************************************************

Minimap:

add enable/disable controls

clamp on the edges or use margin ??**

make tests with rotating the minimap instead of the player
make tests with iso minimap
draw a ring around it ?

**************************************************************************
Elevator:

TODO:
	cleanup elevator (img) (change when oli chooses how to do the buttons)

*ideas*
	do we implement a waiting period
	elevator music ?

	we also need booleans for:
		
		- is player inside (to allow for level change)
			
			*! cue elevator music ? (should we adjust music volume with player's proximity and cut it when doors are closed ?)

incorporate parsing in previous functions to liberate the elevator code


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

- render more stuff so it gets laggy

- invert controls ?

- use the lerp effect with random pixel value



*/

