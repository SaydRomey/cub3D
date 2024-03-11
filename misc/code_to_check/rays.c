/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:24:05 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/19 18:58:25 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 
/*
void drawRays2D()
{
 glColor3f(0,1,1); glBegin(GL_QUADS); glVertex2i(526,  0); glVertex2i(1006,  0); glVertex2i(1006,160); glVertex2i(526,160); glEnd();	
 glColor3f(0,0,1); glBegin(GL_QUADS); glVertex2i(526,160); glVertex2i(1006,160); glVertex2i(1006,320); glVertex2i(526,320); glEnd();	 	
	
 int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
 
 ra=FixAng(pa+30);                                                              //ray set back 30 degrees
 
 for(r=0;r<60;r++)
 {
  //---Vertical--- 
  dof=0; side=0; disV=100000;
  float Tan=tan(degToRad(ra));
	   if(cos(degToRad(ra))> 0.001){ rx=(((int)px>>6)<<6)+64;      ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;}//looking left
  else if(cos(degToRad(ra))<-0.001){ rx=(((int)px>>6)<<6) -0.0001; ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;}//looking right
  else { rx=px; ry=py; dof=8;}                                                  //looking up or down. no hit  

  while(dof<8) 
  { 
   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
   if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  } 
  vx=rx; vy=ry;

  //---Horizontal---
  dof=0; disH=100000;
  Tan=1.0/Tan; 
	   if(sin(degToRad(ra))> 0.001){ ry=(((int)py>>6)<<6) -0.0001; rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;}//looking up 
  else if(sin(degToRad(ra))<-0.001){ ry=(((int)py>>6)<<6)+64;      rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;}//looking down
  else{ rx=px; ry=py; dof=8;}                                                   //looking straight left or right
 
  while(dof<8) 
  { 
   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
   if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  } 
  
  glColor3f(0,0.8,0);
  if(disV<disH){ rx=vx; ry=vy; disH=disV; glColor3f(0,0.6,0);}                  //horizontal hit first
  glLineWidth(2); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();//draw 2D ray
	
  int ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
  int lineH = (mapS*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
  int lineOff = 160 - (lineH>>1);                                               //line offset
  
  glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineOff);glVertex2i(r*8+530,lineOff+lineH);glEnd();//draw vertical wall  

 ra=FixAng(ra-1);                                                              //go to next ray
}
*/

// void drawRays2D()
// {
// 	// Abstract MiniLibX calls to draw rectangles
// 	// mlx_draw_rectangle(mlx_ptr, win_ptr, 526, 0, 480, 160, 0x00FFFFFF);   // Cyan rectangle
// 	// mlx_draw_rectangle(mlx_ptr, win_ptr, 526, 160, 480, 160, 0x0000FFFF); // Blue rectangle

// 	int rayIndex, mapXIndex, mapYIndex, mapPosition, depthOfField, side;
// 	float verticalX, verticalY, rayX, rayY, rayAngle, xOffset, yOffset, distanceVertical, distanceHorizontal;
	
// 	rayAngle = FixAng(playerAngle + 30); // ray set back 30 degrees
// 	rayIndex = 0;

// 	while(rayIndex < 60)
// 	{
// 		//---Vertical---
// 		depthOfField = 0;
// 		side = 0;
// 		distanceVertical = 100000;
// 		float tanAngle = tan(degToRad(rayAngle));

// 		if(cos(degToRad(rayAngle)) > 0.001)
// 		{
// 			rayX = (((int)playerX >> 6) << 6) + 64;
// 			rayY = (playerX - rayX) * tanAngle + playerY;
// 			xOffset = 64;
// 			yOffset = -xOffset * tanAngle;
// 		}
// 		else if(cos(degToRad(rayAngle)) < -0.001)
// 		{
// 			rayX = (((int)playerX >> 6) << 6) - 0.0001;
// 			rayY = (playerX - rayX) * tanAngle + playerY;
// 			xOffset = -64;
// 			yOffset = -xOffset * tanAngle;
// 		}
// 		else
// 		{
// 			rayX = playerX;
// 			rayY = playerY;
// 			depthOfField = 8;
// 		}

// 		while(depthOfField < 8)
// 		{
// 			mapXIndex = (int)(rayX) >> 6;
// 			mapYIndex = (int)(rayY) >> 6;
// 			mapPosition = mapYIndex * mapX + mapXIndex;

// 			if(mapPosition > 0 && mapPosition < mapX * mapY && map[mapPosition] == 1)
// 			{
// 				depthOfField = 8;
// 				distanceVertical = cos(degToRad(rayAngle)) * (rayX - playerX) - sin(degToRad(rayAngle)) * (rayY - playerY);
// 			}
// 			else
// 			{
// 				rayX += xOffset;
// 				rayY += yOffset;
// 				depthOfField += 1;
// 			}
// 		}

// 		verticalX = rayX;
// 		verticalY = rayY;

// 		//---Horizontal---
// 		// Similar logic for horizontal rays...

// 		// Abstract MiniLibX calls to draw rays and walls
// 		// mlx_draw_line(mlx_ptr, win_ptr, playerX, playerY, rayX, rayY, 0x00800000); // Draw 2D ray
// 		// mlx_draw_vertical_line(mlx_ptr, win_ptr, rayIndex * 8 + 530, lineOffset, lineHeight, 0x00FF0000); // Draw vertical wall

// 		rayAngle = FixAng(rayAngle - 1); // go to next ray
// 		rayIndex++;
// 	}
// }
// }

// typedef struct s_ray {
//     t_point start;
//     t_point end;
//     float distance;
//     int hit_side; // 0 for vertical, 1 for horizontal
// } t_ray;

// float fix_angle(float angle);
// float calculate_distance(float angle, t_point start, t_point end);
// void check_ray_hit(t_ray *ray, float angle, int map[][mapX], int mapY, float playerX, float playerY);
// void draw_ray(t_ray *ray /*, Additional MiniLibX parameters for drawing */);

// void draw_rays_2d(float playerX, float playerY, float playerAngle, int map[][mapX], int mapY /*, MiniLibX parameters */)
// {
//     float ray_angle = fix_angle(playerAngle + 30);

//     int r = 0;
//     while (r < 60)
//     {
//         t_ray ray;
//         check_ray_hit(&ray, ray_angle, map, mapY, playerX, playerY);
//         draw_ray(&ray /*, MiniLibX drawing parameters */);

//         ray_angle = fix_angle(ray_angle - 1);
//         r++;
//     }
// }

// /*
// fix_angle: Adjusts the angle to stay within 0-360 degrees.
// calculate_distance: Computes the distance of the ray.
// check_ray_hit: Determines where the ray hits an obstacle and sets the ray properties.
// draw_ray: Handles drawing the ray using MiniLibX 
// */

// float fix_angle(float angle) {
//     while (angle >= 360.0f) angle -= 360.0f;
//     while (angle < 0.0f) angle += 360.0f;
//     return angle;
// }

// float calculate_distance(float angle, t_point start, t_point end) {
//     return cos(degToRad(angle)) * (end.x - start.x) - sin(degToRad(angle)) * (end.y - start.y);
// }

// void check_ray_hit(t_ray *ray, float angle, int map[][mapX], int mapY, float playerX, float playerY) {
//     // Initialize ray values
//     ray->start.x = playerX;
//     ray->start.y = playerY;
//     ray->distance = 100000; // Large initial distance
//     ray->hit_side = 0; // 0 for vertical, 1 for horizontal

//     // Logic to update ray->end based on the map, player position, and angle
//     // Similar to the logic in your original function, split into vertical and horizontal checks

//     // After determining the hit, calculate the distance
//     ray->distance = calculate_distance(angle, ray->start, ray->end);
// }

// void draw_ray(t_ray *ray /*, Additional MiniLibX parameters for drawing */) {
//     // Replace OpenGL drawing commands with MiniLibX drawing commands
//     // Example comment for MiniLibX: Draw a line from ray->start to ray->end
//     // mlx_draw_line(mlx_ptr, win_ptr, ray->start.x, ray->start.y, ray->end.x, ray->end.y, color);
// }


