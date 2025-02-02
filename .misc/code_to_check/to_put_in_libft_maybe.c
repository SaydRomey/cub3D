/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_put_in_libft_maybe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:57:51 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/15 15:11:02 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_clamp(int value, int min, int max)
{
	return (ft_max(ft_min(value, max), min));
}

int	is_within_limits(int value, int min, int max)
{
	if (value < min || value > max)
		return (FALSE);
	return (TRUE);
}

int	ft_strsetcmp(char *str, char *set)
{
	int	i;

	i = 0;
	if (!str || !set)
		return (FALSE);
	while (str[i])
	{
		if (!ft_strchr(set, str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_strvalid(char *str, char *required, char *allowed)
{
	int	valid;
	int	i;

	if (!str || !required || !allowed)
		return (FALSE);
	valid = FALSE;
	i = 0;
	while (str[i])
	{
		if (ft_strchr(required, str[i]))
			valid = TRUE;
		if (!ft_strchr(allowed, str[i]) && !ft_strchr(required, str[i]))
			return (FALSE);
		i++;
	}
	return (valid);
}
