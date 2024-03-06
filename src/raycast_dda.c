/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:49:53 by oroy              #+#    #+#             */
/*   Updated: 2024/03/06 16:50:33 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_hit_data(t_player *p, t_raycast *r)
{
	printf("CHECK HIT\n");
	if (r->side == 0)
	{
		r->wall_perp_dist = r->length.x - r->grid_dist.x;
		r->wall_hit_pos = p->position.y + r->wall_perp_dist * r->ray_dir.y;
	}
	else
	{
		r->wall_perp_dist = r->length.y - r->grid_dist.y;
		r->wall_hit_pos = p->position.x + r->wall_perp_dist * r->ray_dir.x;
	}
	r->wall_hit_pos -= floor(r->wall_hit_pos);
}

// int	check_hit(int map_x, int map_y)
// {
// 	int	map[MAP_HEIGHT][MAP_WIDTH] =
// 	{
// 		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 		{2, 0, 0, 0, 1, 1, 1, 0, 0, 1},
// 		{1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
// 		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
// 	};

// 	// if (map[map_y][map_x] > 0)
// 	// 	return (true);
// 	return (map[map_y][map_x]);
// }

int	check_hit2(int map_x, int map_y, int **map_array)
{
	int	width = 21;
	int	height = 13;
	
	printf("CHECKHIT 2\n");
	if (map_x > width || map_y > height)
	{
		printf("Out of bounds\n");
		return (false);
	}
	else if (map_array[map_y][map_x] > 0)
		return (true);
	return (false);
	// return (map_array[map_y][map_x]);
}

// void	execute_dda_algo(t_player *p, t_raycast *r)
// {
// 	bool	hit;

// 	hit = 0;
// 	while (!hit)
// 	{
// 		if (r->length.x < r->length.y)
// 		{
// 			r->length.x += r->grid_dist.x;
// 			r->ray_pos.x += r->step.x;
// 			r->side = 0;
// 		}
// 		else
// 		{
// 			r->length.y += r->grid_dist.y;
// 			r->ray_pos.y += r->step.y;
// 			r->side = 1;
// 		}
// 		if (check_hit(r->ray_pos.x, r->ray_pos.y) > 0)
// 			hit = 1;
// 	}
// 	get_hit_data(p, r);
// }

void	execute_dda_algo(t_player *p, t_raycast *r, int **map_array)
{
	bool	hit;

	hit = 0;
	printf("\n\niteration\n\n");
	while (!hit)
	{
		printf("r->length.x %f\n", r->length.x);
		printf("r->length.y %f\n", r->length.x);
		printf("r->ray_pos.x %d\n", r->ray_pos.x);
		printf("r->ray_pos.y %d\n", r->ray_pos.y);
		printf("r->step.x %d\n", r->step.x);
		printf("r->step.y %d\n", r->step.y);
		printf("r->grid_dist.x %f\n", r->grid_dist.x);
		printf("r->grid_dist.y %f\n", r->grid_dist.y);
		printf("%s----------%s\n", CYAN, RESET);
		// 
		if (r->length.x < r->length.y)
		{
			r->length.x += r->grid_dist.x;
			r->ray_pos.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->length.y += r->grid_dist.y;
			r->ray_pos.y += r->step.y;
			r->side = 1;
		}
		// if (check_hit(r->ray_pos.x, r->ray_pos.y) > 0)
		if (check_hit2(r->ray_pos.x, r->ray_pos.y, map_array) > 0)
			hit = 1;
		// hit = 1;
	}
	get_hit_data(p, r);
}

