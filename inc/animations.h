#ifndef ANIMATIONS_H
# define ANIMATIONS_H

# include "MLX42.h"
# include "utils.h"

# define FRAME_SPEED	100
# define GO_LEFT		1
# define GO_RIGHT		0

typedef struct s_animation
{
	mlx_image_t	**frames;
	double		accumulator;
	int			frame_speed;
	int			current_frame;
	int			last_frame;
}				t_animation;

typedef struct s_slice
{
	int			total;
	int			width;
	int			height;
	t_point		position;
}				t_slice;

// animation.c
t_animation	set_animation(mlx_image_t *img, int slice_total);
void		update_animation(t_animation *a, bool direction);

#endif // ANIMATIONS_H
