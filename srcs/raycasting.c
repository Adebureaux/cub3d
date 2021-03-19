/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:49:17 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/19 03:14:33 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void 	draw_floor(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	//FLOOR CASTING
	for(int y = 0; y < cub->ry; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = ray->dir.x - ray->pla.x;
		float rayDirY0 = ray->dir.y - ray->pla.y;
		float rayDirX1 = ray->dir.x + ray->pla.x;
		float rayDirY1 = ray->dir.y + ray->pla.y;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - cub->ry / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * cub->ry;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / cub->rx;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / cub->rx;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = ray->pos.x + rowDistance * rayDirX0;
		float floorY = ray->pos.y + rowDistance * rayDirY0;

		for(int x = 0; x < cub->rx; ++x)
		{
		// the cell coord is simply got from the integer parts of floorX and floorY
		int cellX = (int)(floorX);
		int cellY = (int)(floorY);

		// get the texture coordinate from the fractional part
		int tx = (int)(TEX_W * (floorX - cellX)) & (TEX_W - 1);
		int ty = (int)(TEX_H * (floorY - cellY)) & (TEX_H - 1);

		floorX += floorStepX;
		floorY += floorStepY;

		// choose texture and draw the pixel
		int color;

		// floor
		color = ray->tex[5][TEX_W * ty + tx];
		color = (color >> 1) & 8355711; // make a bit darker
		mlx_pixel_draw(mlx, x, y, color);

		// ceiling (symmetrical, at cub->ry - y - 1 instead of y)
		color = cub->c;
		mlx_pixel_draw(mlx, x, cub->ry - y - 1, color);
		}
	}
}

void	draw(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	int		x;
	int		y;

	x = 0;
	draw_floor(cub, mlx, ray);
	while (x < cub->rx)
	{
		double		perpWallDist;
		double cameraX = 2 * x / (double)(cub->rx) - 1;
		double rayDirX = ray->dir.x + ray->pla.x * cameraX;
		double rayDirY = ray->dir.y + ray->pla.y * cameraX;
		int mapX = (int)(ray->pos.x);
		int mapY = (int)(ray->pos.y);
		double sideDistX;
		double sideDistY;
		double deltaDistX;
		double deltaDistY;
		int stepX;
		int stepY;
		int hit = 0;
		int lineHeight;
		int drawStart;
		int drawEnd;


		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (ray->pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - ray->pos.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (ray->pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - ray->pos.y) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				ray->side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				ray->side = 1;
			}
			if (cub->map[mapX][mapY] == '1')
				hit = 1;
		}
		if (ray->side == 0 && rayDirX > 0)
			ray->tex_nbr = 0;
		else if (ray->side == 0 && rayDirX < 0)
			ray->tex_nbr = 1;
		else if (ray->side == 1 && rayDirY < 0)
			ray->tex_nbr = 2;
		else
			ray->tex_nbr = 3;
		if (ray->side == 0)
			perpWallDist = (mapX - ray->pos.x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - ray->pos.y + (1 - stepY) / 2) / rayDirY;
		lineHeight = (int)(cub->ry / perpWallDist);
		drawStart = -lineHeight / 2 + cub->ry / 2;
		if(drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + cub->ry / 2;
		if(drawEnd >= cub->ry)drawEnd = cub->ry - 1;

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (ray->side == 0) wallX = ray->pos.y + perpWallDist * rayDirY;
		else           wallX = ray->pos.x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(TEX_W));
		if(ray->side == 0 && rayDirX > 0) texX = TEX_W - texX - 1;
		if(ray->side == 1 && rayDirY < 0) texX = TEX_W - texX - 1;
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * TEX_H / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - cub->ry / 2 + lineHeight / 2) * step;

		y = drawStart;
		while (y < drawEnd)
		{
			// Cast the texture coordinate to integer, and mask with (TEX_H - 1) in case of overflow
			int texY = (int)texPos & (TEX_H - 1);
			texPos += step;

			//int color = texture[texNum][TEX_H * texY + texX];
			int color = ray->tex[ray->tex_nbr][TEX_H * texY + texX];

			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (ray->side == 1)
				color = (color >> 1) & 8355711;
			mlx_pixel_draw(mlx, x, y, color);
			y++;
		}
		ray->buf[x] = perpWallDist; //perpendicular distance is used
		x++;
	}
	draw_sprite(cub, mlx, ray);
}

void	raycasting(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	draw(cub, mlx, ray);
	mlx_hook(mlx->win, 2, 1L << 0, key_hook, mlx);
	mlx_hook(mlx->win, 33, 1L << 17, quit, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	// mlx_hook(recup->data.mlx_win, 33, 1L << 17, ft_exit, recup);
	// mlx_hook(recup->data.mlx_win, 2, 1L << 0, ft_key_press, recup);
	//mlx_loop_hook(mlx->mlx, draw, mlx);
	// mlx_hook(recup->data.mlx_win, 3, 1L << 1, ft_key_release, recup);
	mlx_loop(mlx->mlx);
}
