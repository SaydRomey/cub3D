#ifndef ASSET_H
# define ASSET_H

# include "MLX42.h"
# include "animations.h"

# define SPRITE_MAX	32

typedef struct s_asset
{
	float		distance;
	int			screen_x;
	t_fpoint	pos;
	t_fpoint	pos_relative;
	t_fpoint	transform;
	t_line		h;
	t_line		v;
	mlx_image_t	*tex;
	t_animation	anim;
}				t_asset;

// assets.c
t_asset	*init_assets(char *texture_path, void *param, int slice_total);
void	update_assets(void *param);

#endif // ASSET_H
