/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:39:56 by cdumais           #+#    #+#             */
/*   Updated: 2024/03/16 20:25:53 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
double  angle = M_PI / 4; // Rotate by 45 degrees
*/
// void	rotate_image(mlx_image_t *src, mlx_image_t *dst, double angle)
// {
// 	int		x;
// 	int		y;
// 	int		new_x;
// 	int		new_y;
// 	int		center_x;
// 	int		center_y;
// 	double	cos_a;
// 	double	sin_a;

// 	center_x = src->width / 2;
// 	center_y = src->height / 2;
// 	cos_a = cos(angle);
// 	sin_a = sin(angle);

// 	y = 0;
// 	while (y < dst->height)
// 	{
// 		x = 0;
// 		while (x < dst->width)
// 		{
// 			new_x = (int)((x - center_x) * cos_a - (y - center_y) * sin_a) + center_x;
// 			new_y = (int)((x - center_x) * sin_a + (y - center_y) * cos_a) + center_y;
// 			draw_pixel(dst, x, y, get_pixel(src, new_x, new_y));
// 			x++;
// 		}
// 		y++;
// 	}
// }

/*
add (double)angle variable to t_minimap to hold current angle of minimap

To rotate the view or the minimap itself,
we essentially need to apply a rotation transformation to the coordinates of each element
(like the player direction or enemies) you draw on the minimap.

The rotation formula for a point (x, y) around a pivot point (cx, cy) by an angle theta is as follows:

x' = cos(theta) * (x - cx) - sin(theta) * (y - cy) + cx;
y' = sin(theta) * (x - cx) + cos(theta) * (y - cy) + cy;


*/

// Applying Rotation to the Minimap
// If you opt to rotate the entire minimap image after it's been drawn
// (before applying the circular mask in make_it_round), you would essentially:

// Draw the minimap as if it were not rotated (ignore the angle).
// Create a new image where you would copy the minimap pixels to, applying the rotation based on the angle.
// Apply the circular mask to the rotated image.
// This method requires a function to rotate the whole image,
// which can be adapted from the pseudocode provided in the earlier response regarding rotating images.
// However, keep in mind that efficiently implementing such functionality
// requires a good understanding of image processing techniques and might not be straightforward.

// For real-time applications,
// especially in games or simulations,
// it's often more practical to rotate elements within the minimap
// (like the player's direction) rather than attempting to rotate the entire map or its tiles individually.
// This approach simplifies calculations, reduces computational overhead, and is generally easier to integrate with game logic.


