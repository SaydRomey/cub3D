/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_put_in_libft_maybe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:57:51 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/27 15:57:55 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_within_limits(int value, int min, int max)
{
	if (value < min || value > max)
		return (FALSE);
	return (TRUE);
}


