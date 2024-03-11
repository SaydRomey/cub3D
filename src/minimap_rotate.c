// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   minimap_rotate.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/11 15:39:56 by cdumais           #+#    #+#             */
// /*   Updated: 2024/03/11 15:40:07 by cdumais          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3d.h"

// Yes, implementing a function to rotate an image by a chosen angle (in degrees or radians) is definitely possible and a common operation in graphics programming. When using MLX, which is a library often used in projects at 42's coding school and similar environments for learning graphics programming, you'd typically need to work at a lower level than you would with high-level graphics or game development libraries.

// To rotate an image, you'll generally need to:

// Create a new blank image that will hold the rotated version of the original image.
// Iterate through each pixel of the new image, mapping it back to the corresponding pixel in the original image. This involves a bit of math, specifically using rotation matrices.
// Apply rotation around the center of the image or another chosen pivot point, which involves calculating the new positions of each pixel after rotation.
// Handle pixels that fall outside the bounds of the original image.
// The rotation of a point 
// (
// �
// ,
// �
// )
// (x,y) around another point 
// (
// �
// pivot
// ,
// �
// pivot
// )
// (x 
// pivot
// ​
//  ,y 
// pivot
// ​
//  ) by an angle 
// �
// θ (in radians) is given by the transformation:

// �
// ′
// =
// cos
// ⁡
// (
// �
// )
// ⋅
// (
// �
// −
// �
// pivot
// )
// −
// sin
// ⁡
// (
// �
// )
// ⋅
// (
// �
// −
// �
// pivot
// )
// +
// �
// pivot
// �
// ′
// =
// sin
// ⁡
// (
// �
// )
// ⋅
// (
// �
// −
// �
// pivot
// )
// +
// cos
// ⁡
// (
// �
// )
// ⋅
// (
// �
// −
// �
// pivot
// )
// +
// �
// pivot
// x 
// ′
 
// y 
// ′
 
// ​
  
// =cos(θ)⋅(x−x 
// pivot
// ​
//  )−sin(θ)⋅(y−y 
// pivot
// ​
//  )+x 
// pivot
// ​
 
// =sin(θ)⋅(x−x 
// pivot
// ​
//  )+cos(θ)⋅(y−y 
// pivot
// ​
//  )+y 
// pivot
// ​
 
// ​
 
// This transformation can be applied to each pixel in the image. However, because you're working with discrete pixel values, you might need to use some form of interpolation (like nearest neighbor or bilinear interpolation) to get the best visual results for pixels that don't align perfectly after rotation.

// Would you like a more detailed example in pseudo-code or C code on how to implement such a function, including the necessary steps and mathematical operations?

// User
// Yes show me the full C code please
// ChatGPT
// Below is an example of how you might implement a simple image rotation function in C using the MLX library. This example assumes you have a basic understanding of the MLX library and its functions for creating images, manipulating pixels, etc. The example focuses on rotating an image around its center by a specified angle in radians. It's a basic implementation and might need adjustments based on your specific requirements, especially in terms of handling the edges and corners of the image.

// This code does not handle cases where the rotated image would require a larger canvas to fit without clipping, nor does it implement any interpolation for smoothing. You might need to adjust the image dimensions or apply interpolation techniques for a smoother result.

// c
// Copy code
// #include <mlx.h>
// #include <math.h>

// typedef struct s_img {
//     void    *img_ptr;
//     char    *data;
//     int     width;
//     int     height;
//     int     bpp;
//     int     size_line;
//     int     endian;
// }           t_img;

// void    put_pixel_to_img(t_img *img, int x, int y, int color) {
//     if (x >= 0 && x < img->width && y >= 0 && y < img->height)
//         *(int *)(img->data + ((x + y * img->width) * img->bpp / 8)) = color;
// }

// int     get_pixel_from_img(t_img *img, int x, int y) {
//     if (x >= 0 && x < img->width && y >= 0 && y < img->height)
//         return *(int *)(img->data + ((x + y * img->width) * img->bpp / 8));
//     return 0;
// }

// void    rotate_image(t_img *src, t_img *dst, double angle) {
//     int     x, y;
//     int     new_x, new_y;
//     int     center_x = src->width / 2;
//     int     center_y = src->height / 2;
//     double  cos_a = cos(angle);
//     double  sin_a = sin(angle);

//     for (y = 0; y < dst->height; y++) {
//         for (x = 0; x < dst->width; x++) {
//             new_x = (int)((x - center_x) * cos_a - (y - center_y) * sin_a) + center_x;
//             new_y = (int)((x - center_x) * sin_a + (y - center_y) * cos_a) + center_y;
//             put_pixel_to_img(dst, x, y, get_pixel_from_img(src, new_x, new_y));
//         }
//     }
// }

// int main() {
//     void    *mlx_ptr;
//     void    *win_ptr;
//     t_img   src_img;
//     t_img   dst_img;
//     double  angle = M_PI / 4; // Rotate by 45 degrees

//     mlx_ptr = mlx_init();
//     win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Rotate Image");

//     // Assuming src_img is already loaded with an image
//     // Initialize src_img & dst_img properly (e.g., loading src_img, setting width, height)
    
//     // Create an empty image for dst_img
//     dst_img.img_ptr = mlx_new_image(mlx_ptr, src_img.width, src_img.height);
//     dst_img.data = mlx_get_data_addr(dst_img.img_ptr, &dst_img.bpp, &dst_img.size_line, &dst_img.endian);
//     dst_img.width = src_img.width;
//     dst_img.height = src_img.height;
    
//     // Rotate src_img and store the result in dst_img
//     rotate_image(&src_img, &dst_img, angle);

//     // Display the result
//     mlx_put_image_to_window(mlx_ptr, win_ptr, dst_img.img_ptr, 0, 0);
//     mlx_loop(mlx_ptr);
//     return 0;
// }
// This example assumes you have already loaded or created an image in src_img before calling rotate_image. It also assumes that dst_img is correctly initialized and is the same size as src_img.

// Remember, this is a simplified example. In a real application, you would need to handle various edge cases, potentially resize the destination image to prevent clipping, and possibly apply smoothing or interpolation to improve the visual quality of the rotated image.


// 2 / 2

// User
// Lets say i wanted to add an 'angle' variable to my 't_minimap' struct, and adapt the make it round() function to rotate in here:

// t_minimap        init_minimap(t_cub *cub)
// {
//         t_minimap        mini;

//         ft_memset(&mini, 0, sizeof(t_minimap)); //not necessary if minimap is inside t_cub ? (already memset)
//         // 
//         mini.img = new_img(cub->mlx, WIDTH / 3, WIDTH / 3, true);
//         mini.img->instances->x = WIDTH - mini.img->width; //place on the right
//         // 
//         mini.round_img = new_img(cub->mlx, WIDTH / 3, WIDTH / 3, true);
//         // 
//         mini.tile_size = 42;
//         // 
//         return (mini);

// }

// static int        tile_color(int y, int x)
// {
//         int                        value;
//         t_fpoint        position;

//         value = call_cub()->map.map_array[y][x];
//         position = call_cub()->player.position;

//         if (x == (int)position.x && y == (int)position.y)
//                 return (HEX_PURPLE);
//         else if (value == 0)
//                 return (HEX_GREEN);
//         else if (value == 1)
//                 return (HEX_ORANGE);
//         else if (value == 2) //door?
//                 return (HEX_BLUE);
//         else if (value == -1 || value == -2)
//                 return (HEX_GRAY);
//         else
//                 return (HEX_RED); //should not get here
// }

// static void        draw_tile(mlx_image_t *img, t_point origin, t_point size, int color)
// {
//         int        x;
//         int        y;

//         y = origin.y;
//         while (y < origin.y + size.y)
//         {
//                 x = origin.x;
//                 while (x < origin.x + size.x)
//                 {
//                         draw_pixel(img, x, y, color);
//                         x++;
//                 }
//                 y++;
//         }
// }

// static void        draw_tiles(t_minimap *minimap, t_point start, t_point end)
// {
//         int                x;
//         int                y;
//         t_point        tile;
//         t_point        size;

//         size.x = minimap->tile_size - 1;
//         size.y = minimap->tile_size - 1;
//         y = start.y;
//         while (y < end.y)
//         {
//                 x = start.x;
//                 while (x < end.x)
//                 {
//                         tile.x = (x - start.x) * minimap->tile_size;
//                         tile.y = (y - start.y) * minimap->tile_size;
//                         draw_tile(minimap->img, tile, size, tile_color(y, x));
//                         x++;
//                 }
//                 y++;
//         }
// }

// /* ************************************************************************** */

// /* maybe put in libft? */
// int        ft_clamp(int value, int min, int max)
// {
//         return (ft_max(ft_min(value, max), min));
// }

// static t_point        find_center(t_minimap *minimap, t_map *map)
// {
//         int                        half_width;
//         int                        half_height;
//         t_fpoint        pos;
//         t_point                center;

//         half_width = minimap->img->width / (2 * minimap->tile_size);
//         half_height = minimap->img->height / (2 * minimap->tile_size);
//         pos = call_cub()->player.position;
//         center.x = ft_clamp((int)pos.x, half_width, map->width - half_width);
//         center.y = ft_clamp((int)pos.y, half_height, map->height - half_height);
//         return (center);
// }

// static void        calculate_bounds(t_point center, t_point *start, t_point *end)
// {
//         int                half_width;
//         int                half_height;
//         // t_point        center;
//         t_minimap        *minimap = &call_cub()->minimap;

//         half_width = minimap->img->width / (2 * minimap->tile_size);
//         half_height = minimap->img->height / (2 * minimap->tile_size);
//         start->x = center.x - half_width;
//         start->y = center.y - half_height;
//         end->x = center.x + half_width;
//         end->y = center.y + half_height;
// }

// /* ************************************************************************** */ //circle map

// static bool        is_in_circle(t_point point, t_point center, int radius)
// {
//         t_point        distance;

//         distance.x = point.x - center.x;
//         distance.y = point.y - center.y;
//         return ((distance.x * distance.x + distance.y * distance.y) <= radius * radius);
//         // return (pow(point.x - center.x, 2) + pow(point.y - center.y, 2)) <= pow(radius, 2);

// }

// static void        make_it_round(t_minimap *minimap, t_map *map)
// {
//         int                radius = minimap->round_img->width / 3;
//         t_point        circle_center = {radius, radius};

//         int        map_width = map->width * minimap->tile_size;
//         int        map_height = map->height * minimap->tile_size;

//         t_fpoint        pos = call_cub()->player.position;

//         int        center_offset_x = (int)pos.x - radius;
//         int        center_offset_y = (int)pos.y - radius;

//         center_offset_x = ft_clamp(center_offset_x, 0, map_width - minimap->round_img->width);
//         center_offset_y = ft_clamp(center_offset_y, 0, map_height - minimap->round_img->height);

//         int        x;
//         int        y;

//         y = 0;
//         while (y < (int)minimap->round_img->height)
//         {
//                 x = 0;
//                 while (x < (int)minimap->round_img->width)
//                 {
//                         if (is_in_circle((t_point){x, y}, circle_center, radius))
//                         {
//                                 int        map_x = center_offset_x + x;
//                                 int        map_y = center_offset_y + y;

//                                 int        color = get_pixel(minimap->img, map_x, map_y);

//                                 draw_pixel(minimap->round_img, x, y, color);
//                         }
//                         x++;
//                 }
//                 y++;
//         }
// }

// /* ************************************************************************** */ //features (options)

// static int        adjust_tile_size(mlx_image_t *img, t_map *map)
// {
//         int        tile_width;
//         int        tile_height;

//         tile_width = img->width / map->width;
//         tile_height = img->height / map->height;
//         return (ft_min(tile_width, tile_height));
// }

// static void        features_testing(t_minimap *minimap, t_map *map)
// {
//         bool        dynamic = false;

//         if (dynamic == true)
//                 minimap->tile_size = adjust_tile_size(minimap->img, map);

// }

// /* ************************************************************************** */

// void        draw_mini_player(t_minimap *minimap, t_player *player)
// {
//         t_fpoint        line_size;
//         int                        ray_length = 42; //tmp
//         int                        ray_color = 0x00FF00FF; //tmp

//         line_size.x = player->position.x + player->delta.x * ray_length;
//         line_size.y = player->position.y + player->delta.y * ray_length;
//         draw_line(minimap->img, player->position, line_size, ray_color);
//         draw_circle(minimap->img, player->position, player->size, player->color);
// }

// void        draw_minimap(t_minimap *minimap, t_map *map)
// {
//         t_point        start;
//         t_point        end;

//         clear_img(minimap->img);
//         clear_img(minimap->round_img);
//         if (call_cub()->keys.m)
//         {
//                 features_testing(minimap, map);
//                 calculate_bounds(find_center(minimap, map), &start, &end);
//                 draw_tiles(minimap, start, end);
//                 draw_mini_player(minimap, &call_cub()->player);

//                 make_it_round(minimap, map);
//         }
// }
// ChatGPT
// To incorporate rotation into your t_minimap struct and adapt the make_it_round function to rotate the minimap based on an angle, you need to perform several steps. I'll guide you through the necessary modifications and additions:

// Add an Angle Variable to Your t_minimap Struct: Add a double angle; member to hold the current rotation angle of the minimap.

// Modify the Drawing Functions: You'll need to adjust how you draw each tile in the minimap to account for the rotation. This involves calculating the position of each tile after rotation and then drawing it in the new position.

// Here's an outline of the steps and some code snippets to illustrate how to implement these changes:

// Step 1: Modify t_minimap Structure
// Add the angle variable to your t_minimap structure.

// c
// Copy code
// typedef struct s_minimap {
//     // Your existing fields...
//     double angle; // Angle in radians
// } t_minimap;
// Step 2: Update the draw_tile Function
// To rotate the tiles, you should calculate their new positions based on the minimap's rotation angle. However, rotating individual tiles while trying to maintain a coherent map structure, especially in a pixel-based approach, can be quite complex and computationally expensive for a real-time application like a game.

// Instead, consider rotating the player's view within the minimap (i.e., the direction the player is facing) or rotating the entire minimap image after it has been drawn (which still involves significant reworking of how pixels are manipulated).

// For simplicity and practicality, I'll show you how to adjust for rotation in a conceptual manner that you would apply when drawing the player's direction or potentially rotating the entire minimap after drawing:

// Conceptual Adjustment for Rotation
// When you want to rotate the view or the minimap itself, you essentially need to apply a rotation transformation to the coordinates of each element (like the player direction or enemies) you draw on the minimap. The rotation formula for a point (x, y) around a pivot point (cx, cy) by an angle theta is as follows:

// c
// Copy code
// x' = cos(theta) * (x - cx) - sin(theta) * (y - cy) + cx;
// y' = sin(theta) * (x - cx) + cos(theta) * (y - cy) + cy;
// Applying Rotation to the Minimap
// If you opt to rotate the entire minimap image after it's been drawn (before applying the circular mask in make_it_round), you would essentially:

// Draw the minimap as if it were not rotated (ignore the angle).
// Create a new image where you would copy the minimap pixels to, applying the rotation based on the angle.
// Apply the circular mask to the rotated image.
// This method requires a function to rotate the whole image, which can be adapted from the pseudocode provided in the earlier response regarding rotating images. However, keep in mind that efficiently implementing such functionality requires a good understanding of image processing techniques and might not be straightforward.

// For real-time applications, especially in games or simulations, it's often more practical to rotate elements within the minimap (like the player's direction) rather than attempting to rotate the entire map or its tiles individually. This approach simplifies calculations, reduces computational overhead, and is generally easier to integrate with game logic.
