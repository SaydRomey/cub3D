/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:53:13 by oroy              #+#    #+#             */
/*   Updated: 2024/04/17 15:34:46 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_asset	*init_assets(char *texture_path)
{
	mlx_image_t	*texture;
	t_asset		*assets;
	int			i;

	assets = ft_calloc(NUMSPRITES, sizeof (t_asset));
	if (!assets)
		return (NULL);
	assets[0].pos = (t_fpoint){6.5, 5.5};
	assets[1].pos = (t_fpoint){6.5, 4.5};
	texture = load_png(texture_path, call_cub()->mlx);
	if (!texture)
		return (NULL);
	i = 0;
	while (i < NUMSPRITES)
	{
		assets[i].tex = texture;
		i++;
	}
	return (assets);
}
