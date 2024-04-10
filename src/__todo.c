/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __todo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:31:55 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/10 16:56:53 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO:
cleanup non-used functions and files, and put functions in proper files

connect rest of code.. next is elevator (need info from oli)..

**************************************************************************

Minimap:

render player or player position in minimap

continue working on radar version of minimap


**************************************************************************
Elevator:

*ideas*
	can we select which level ?
	do we make a elevator ui with adaptative amount of buttons ?
	do we implement a waiting period
	elevator music ?


modify the struct logic..

	*in 't_level' node
	{
		[...]
		t_point	elevator_position;
		int		elevator_orientation; //in radians ?
		char	elevator_orientation; //as a char? check with oli which is better
	}

	*int 't_elevator' struct (common throughout every levels)
	{
		bool	player_in_range (for door animation) *i guess with automatic door, no need for collision logic.?
		bool	player_is_inside (to allow for level change and level choice ?)
		
		[..]animations, textures, etc.
	}

	we also need booleans for:
		
		- is player inside (to allow for level change)
			
			*! cue elevator music ? (should we adjust music volume with player's proximity and cut it when doors are closed ?)

incorporate parsing in previous functions to liberate the elevator code

** !!!to be valid (check with oli):

	- only one per level
	- only one adjacent walkable space
	- exactly three adjacent walls

** ?? Do we allow level skip ?
example:
	level 0 has an elevator,
	level 1 does not,
	level 2 has an elevator...

	can we still get from lvl 0 to lvl 1, and lvl 1 to lvl 0, or does this trigger segworld ?

**************************************************************************
**************************************************************************

TODO maybe:

add '%f' in ft_printf ? and maybe width also ?

create tutorial or instruction menu ? (mouse for clicking on elevator buttons)

full ui ?

**************************************************************************
Segworld:


if one of the levels does not have an elevator,
and the player tries to get to it through an elevator,
we go into segworld, and the elevator breaks... TUN TUN TUNNNNH !!!

- add flickering lights, shadow effect

- render more stuff so it gets laggy

- invert controls ?

- use the lerp effect with random pixel value

// change all colors to unsigned ?


*/

