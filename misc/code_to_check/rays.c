/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:24:05 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/31 23:56:41 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*

#define G_MAP_X 8
#define G_MAP_Y 8
#define G_MAP_S 64

static int g_map[] = {
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,1,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,
};

typedef struct s_fpoint
{
	float		x;
	float		y;
}				t_fpoint;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	float		px;
	float		py;
	float		pdx;
	float		pdy;
	float		pa;
}				t_game;

static float	deg_to_rad(int a);
static int		fix_angle(int a);
static void		draw_map_2d(t_game *game);
static void		draw_player_2d(t_game *game);
static void		handle_input(mlx_key_data_t keydata, t_game *game);
static void		game_loop(t_game *game);

static float	deg_to_rad(int a)
{
	return (a * (M_PI / 180.0f));
}

static int	fix_angle(int a)
{
	while (a >= 360)
		a -= 360;
	while (a < 0)
		a += 360;
	return (a);
}

static void	draw_map_2d(t_game *game)
{
	int	color;

	int x, y;
	y = 0;
	while (y < G_MAP_Y)
	{
		x = 0;
		while (x < G_MAP_X)
		{
			if (g_map[y * G_MAP_X + x] == 1)
				color = 0xFFFFFFFF;
			else
				color = 0x000000FF
			// color = g_map[y * G_MAP_X + x] == 1 ? 0xFFFFFF : 0x000000;
			t_fpoint	start = {x * G_MAP_S, y * G_MAP_S};
			t_fpoint	end = {G_MAP_S, G_MAP_S};
			draw_rectangle(game->img, start, end, color);
			x++;
		}
		y++;
	}
}

static void	draw_player_2d(t_game *game)
{
	t_fpoint	end;

	mlx_draw_rectangle(game->img, game->px - 2, game->py - 2, 4, 4, 0xFFFF00);
	end = {game->px + game->pdx * 20, game->py + game->pdy * 20};
	mlx_draw_line(game->img, (t_fpoint){game->px, game->py}, end, 0xFFFF00);
}

static void	handle_input(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		game->pa += 5;
		game->pa = fix_angle(game->pa);
		game->pdx = cos(deg_to_rad(game->pa));
		game->pdy = sin(deg_to_rad(game->pa));
	}
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		game->pa -= 5;
		game->pa = fix_angle(game->pa);
		game->pdx = cos(deg_to_rad(game->pa));
		game->pdy = sin(deg_to_rad(game->pa));
	}
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		game->px += game->pdx * 5;
		game->py += game->pdy * 5;
	}
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		game->px -= game->pdx * 5;
		game->py -= game->pdy * 5;
	}
}

static void	game_loop(t_game *game)
{
	mlx_clear_window(game->mlx);
	draw_map_2d(game);
	draw_player_2d(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

int	main(void)
{
	t_game	game;

	game.mlx = mlx_init(1024, 510, "42 Game", false);
	if (!game.mlx)
	{
		return (EXIT_FAILURE);
	}
	game.img = mlx_new_image(game.mlx, 1024, 510);
	game.px = 150;
	game.py = 400;
	game.pa = 90;
	game.pdx = cos(deg_to_rad(game.pa));
	game.pdy = sin(deg_to_rad(game.pa));
	mlx_key_hook(game.mlx, (void *)&handle_input, &game);
	mlx_loop_hook(game.mlx, (void *)&game_loop, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}

*/
