/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:39:51 by cdumais           #+#    #+#             */
/*   Updated: 2024/04/29 15:37:24 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// error.c
void	set_error(char *str);
void	set_error_arg(char *str, char *arg);
char	*get_error(void);
void	error(void);
void	error_mlx(void);

#endif // ERROR_H
