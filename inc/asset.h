#ifndef ASSET_H
# define ASSET_H

# include "MLX42.h"
# include "animations.h"
# include "map.h"

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
	bool		is_animated;
}				t_asset;

// assets_utils.c
bool	is_near_elevator(t_map *map, int x, int y);

// assets.c
t_asset	*init_assets(char *texture_path, void *param, int slice_total);
void	update_assets(void *param);

#endif // ASSET_H
