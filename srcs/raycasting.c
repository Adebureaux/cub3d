/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:49:17 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/20 02:35:53 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int		mlx_verline(t_cub *cub, t_mlx *mlx)
{
	// if (mlx->pos.y2 < mlx->pos.y1)
	// {
	// 	mlx->pos.y1 += mlx->pos.y2;
	// 	mlx->pos.y2 = mlx->pos.y1 - mlx->pos.y2;
	// 	mlx->pos.y1 -= mlx->pos.y2;
	// }
	// if (mlx->pos.y2 < 0 || mlx->pos.y1 >= cub->ry
	// 	|| cub->rx < 0 || mlx->pos.y2 >= cub->ry)
	// 	return (0);
	// if (mlx->pos.y1 < 0)
	// 	mlx->pos.y1 = 0;
	// if (mlx->pos.y2 >=  cub->ry)
	// 	mlx->pos.y2 =  cub->rx - 1;
	printf("ICI x = %d, y1 = %d, y2 = %d\n", mlx->pos.x, mlx->pos.y1, mlx->pos.y2);
	while (mlx->pos.y1 < mlx->pos.y2)
	{
		mlx_pixel_put(mlx->mlx, mlx->win, cub->rx, mlx->pos.y1, mlx->color);
		mlx->pos.y1++;
	}
	return (1);
}

void	raycasting(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	(void)ray;
	double	posX = (double)cub->start.x;
	double	posY = (double)cub->start.y;  //x and y start position
	double	dirX = -1, dirY = 0; //initial direction vector
	double	planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	int w = cub->rx;

	mlx->pos.x = 1;
	mlx->pos.y1 = 1;
	mlx->pos.y2 = 500;
	mlx->color = 0x00FF0000;
	printf("x = %d, y1 = %d, y2 = %d\n", mlx->pos.x, mlx->pos.y1, mlx->pos.y2);
	mlx_verline(cub, mlx);
	while (1)
	{
		for(int x = 0; x < w; x++)
		{
			//calculate ray position and direction
			double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;

			//which box of the map we're in
			int mapX = (int)posX;
			int mapY = (int)posY;

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			//length of ray from one x or y-side to next x or y-side
			double deltaDistX = fabs(1 / rayDirX);
			double deltaDistY = fabs(1 / rayDirY);
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?
			deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
			deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));

			//calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}

			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, OR in x-direction, OR in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				if (cub->map[mapX][mapY] != 'O')
					hit = 1;
			}

			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
			if (side == 0)
				perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

			//Calculate height of line to draw on screen
			int h = cub->ry;
			int lineHeight = (int)(h / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + h / 2;
				if (drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + h / 2;
			if (drawEnd >= h)
				drawEnd = h - 1;

			//choose wall color
			mlx->color = 0x00FF0000;
			// switch(cub->map[mapX][mapY])
			// {
			// 	case 1:  color = RGB_Red;  break; //red
			// 	case 2:  color = RGB_Green;  break; //green
			// 	case 3:  color = RGB_Blue;   break; //blue
			// 	case 4:  color = RGB_White;  break; //white
			// 	default: color = RGB_Yellow; break; //yellow
			// }

			//give x and y sides different brightness
			mlx->pos.x = x;
			mlx->pos.y1 = 1;
			mlx->pos.y2 = 500;
			printf("x = %d, y1 = %d, y2 = %d\n", mlx->pos.x, mlx->pos.y1, mlx->pos.y2);
			if (mlx_verline(cub, mlx))
				printf("HEY\n");
			else
				printf("NON\n");
		}
		mlx_hook(mlx->win, 2, 1L<<0, key_hook, mlx);
		mlx_loop(mlx->mlx);
	}
}
