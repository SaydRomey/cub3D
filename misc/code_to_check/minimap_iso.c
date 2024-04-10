// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   minimap_iso.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/11 15:41:04 by cdumais           #+#    #+#             */
// /*   Updated: 2024/03/11 15:42:09 by cdumais          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3d.h"

// static t_point project_iso(t_point point, float iso_angle)
// {
//     t_point projected;
//     // Assuming iso_angle is in radians. If you're using degrees, convert it first.
//     projected.x = (point.x - point.y) * cos(iso_angle);
//     projected.y = ((point.x + point.y) * sin(iso_angle)) / 2; // Dividing by 2 to reduce vertical stretching
//     return projected;
// }

// static void draw_centered_minimap(t_minimap *minimap, t_map *map)
// {
//     t_point center;
//     int half_width;
//     int half_height;

//     half_width = minimap->img->width / (2 * minimap->tile_size);
//     half_height = minimap->img->height / (2 * minimap->tile_size);

//     // Calculate center based on player position, ensuring it's not out of bounds
//     center = find_center(map, half_width, half_height);

//     t_point start;
//     t_point end;

//     start.x = center.x - half_width;
//     start.y = center.y - half_height;
//     end.x = center.x + half_width;
//     end.y = center.y + half_height;

//     // Adjust for the image's dimensions
//     t_point tile;
//     t_point iso_tile;
//     t_point size;
//     size.x = minimap->tile_size - 1;
//     size.y = minimap->tile_size - 1;

//     float iso_angle = M_PI / 4; // 45 degrees in radians

//     int x, y;

//     y = start.y;
//     while (y < end.y)
//     {
//         x = start.x;
//         while (x < end.x)
//         {
//             // Translate map coordinates to image coordinates
//             tile.x = (x - start.x) * minimap->tile_size;
//             tile.y = (y - start.y) * minimap->tile_size;

//             // Apply isometric projection to the tile position
//             iso_tile = project_iso(tile, iso_angle);

//             // Adjust iso_tile position to keep the map centered
//             iso_tile.x += minimap->img->width / 4; // These adjustments depend on your viewport and map size
//             iso_tile.y += minimap->img->height / 8; // Adjust as necessary to center the map

//             if (x >= 0 && x < map->width && y >= 0 && y < map->height)
//                 draw_tile(minimap->img, iso_tile, size, tile_color(y, x));
//             x++;
//         }
//         y++;
//     }
// }

// /*
// The modified draw_centered_minimap function I provided earlier will position the tiles in an isometric layout by adjusting their starting coordinates according to an isometric projection. However, because the draw_tile function still draws each tile as a square (or rectangle, depending on the size parameter), the result will not look like a grid of isometric tiles in the traditional sense where each tile is a diamond shape. Instead, the tiles will be positioned in an isometric pattern but will retain their original square shapes.

// To truly draw an isometric grid where each tile is a diamond shape, additional changes are needed. You have to adjust the draw_tile function to draw diamonds instead of squares. This involves calculating the points of a diamond-shaped tile based on the isometric projection and drawing lines or filling in the space between those points.

// Here's a conceptual outline of how you might modify the draw_tile function to draw isometric (diamond-shaped) tiles:

// */

// static void draw_isometric_tile(mlx_image_t *img, t_point origin, int size, int color)
// {
//     // Calculate the four corners of the diamond-shaped tile
//     t_point top = {origin.x, origin.y - size / 2};
//     t_point left = {origin.x - size / 2, origin.y};
//     t_point right = {origin.x + size / 2, origin.y};
//     t_point bottom = {origin.x, origin.y + size / 2};

//     // Draw lines between the points or fill the diamond shape
//     // For simplicity, here's how you might draw the four lines of the diamond
//     draw_line(img, top, left, color);
//     draw_line(img, left, bottom, color);
//     draw_line(img, bottom, right, color);
//     draw_line(img, right, top, color);
//     // Optionally, fill in the diamond shape with color
// }

// // Adjust draw_centered_minimap to use draw_isometric_tile

// static void draw_filled_isometric_tile(mlx_image_t *img, t_point origin, int size, int color)
// {
//     int height = size; // The vertical height of the diamond
//     int width = size * 2; // The maximum width of the diamond

//     // Calculate the center point of the top of the diamond
//     t_point top = {origin.x, origin.y - height / 2};

//     // Loop from the top of the diamond to the bottom
//     for (int y = 0; y < height; y++)
//     {
//         // Determine the current width of the slice of the diamond
//         // This calculation finds the distance from the center line, then scales it by the aspect ratio
//         int currentWidth = (y < height / 2 ? y : height - y - 1) * 2;

//         // Calculate the starting and ending X coordinates for the current slice
//         int startX = origin.x - currentWidth;
//         int endX = origin.x + currentWidth;

//         // Draw a horizontal line for the current slice of the diamond
//         for (int x = startX; x <= endX; x++)
//         {
//             draw_pixel(img, x, top.y + y, color);
//         }
//     }
// }

// int currentWidth;
// if (y < height / 2) {
//     currentWidth = y * 2;
// } else {
//     currentWidth = (height - y - 1) * 2;
// }

// /*
// Objective: The goal is to draw a diamond shape, which can be visualized as two triangles (top and bottom) joined at their bases. The width of each horizontal line (slice of the diamond) changes as you move from the top of the diamond to the center, and then it decreases symmetrically as you move from the center to the bottom.

// Determining currentWidth:

// The diamond's height is divided into two equal parts: the upper half and the lower half.
// As you start from the top of the diamond and move towards the middle, the width of each horizontal slice increases. This is because the slices are part of the upper triangle, and their width grows as they approach the triangle's base (the widest part of the diamond).
// The variable y tracks the current vertical position within the diamond, starting from 0 at the top.
// When y is less than half of the diamond's height (height / 2), you're in the upper half of the diamond. The width of the horizontal slices (currentWidth) at this stage increases linearly with y. Specifically, it's y * 2 to ensure the diamond scales correctly in width as you move downwards. This is because for each step down, the width of the slice increases to create the sloping sides of the upper triangle.
// Once y reaches the midpoint (height / 2), the logic needs to reverse because you're now drawing the lower half of the diamond, which tapers back to a point. The condition in the else part handles this by calculating the width based on how far y is from the bottom of the diamond. (height - y - 1) * 2 calculates the width of the slices in the lower triangle, decreasing linearly as y increases, creating the sloping sides of the lower triangle.
// */