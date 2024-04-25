#ifndef SEGWORLD_H
# define SEGWORLD_H

# define SW_F_BRIGHT_LVL	128
# define SW_C_BRIGHT_LVL	128

typedef struct s_segworld
{
	mlx_image_t	*user_img;
	mlx_image_t	*wall_textures[4];


}		t_segworld;

// segworld.c
void 	replace_with_segworld(t_level *next_lvl);

#endif // SEGWORLD_H
