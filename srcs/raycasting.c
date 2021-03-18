/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:49:17 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/18 18:34:53 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	mov_up(t_cub *cub, t_ray *ray)
{
	char	pos;

	pos = cub->map[(int)(ray->pos.x + ray->dir.x * MOV_S)][(int)(ray->pos.y)];
	if (pos == 'O' || pos == 'X')
		ray->pos.x += ray->dir.x * MOV_S;
	pos = cub->map[(int)(ray->pos.x)][(int)(ray->pos.y + ray->dir.y * MOV_S)];
	if (pos == 'O' || pos == 'X')
		ray->pos.y += ray->dir.y * MOV_S;
}

void	mov_down(t_cub *cub, t_ray *ray)
{
	char	pos;

	pos = cub->map[(int)(ray->pos.x - ray->dir.x * MOV_S)][(int)(ray->pos.y)];
	if (pos == 'O' || pos == 'X')
		ray->pos.x -= ray->dir.x * MOV_S;
	pos = cub->map[(int)(ray->pos.x)][(int)(ray->pos.y - ray->dir.y * MOV_S)];
	if (pos == 'O' || pos == 'X')
		ray->pos.y -= ray->dir.y * MOV_S;
}

void	mov_left(t_cub *cub, t_ray *ray)
{
	char	pos;

	pos = cub->map[(int)(ray->pos.x - ray->pla.x * MOV_S)]
					[(int)(ray->pos.y - ray->pla.y * MOV_S)];
	if (pos == 'O' || pos == 'X')
	{
		ray->pos.x -= ray->pla.x * MOV_S / 2;
		ray->pos.y -= ray->pla.y * MOV_S / 2;
	}
}

void	mov_right(t_cub *cub, t_ray *ray)
{
	char	pos;

	pos = cub->map[(int)(ray->pos.x + ray->pla.x * MOV_S)]
					[(int)(ray->pos.y - ray->pla.y * MOV_S)];
	if (pos == 'O' || pos == 'X')
	{
		ray->pos.x += ray->pla.x * MOV_S / 2;
		ray->pos.y += ray->pla.y * MOV_S / 2;
	}
}

void	rot_right(t_ray *ray)
{
	double	dirx;
	double	plax;

	dirx = ray->dir.x;
	ray->dir.x = ray->dir.x * cos(-ROT_S) - ray->dir.y * sin(-ROT_S);
	ray->dir.y = dirx * sin(-ROT_S) + ray->dir.y * cos(-ROT_S);
	plax = ray->pla.x;
	ray->pla.x = ray->pla.x * cos(-ROT_S) - ray->pla.y * sin(-ROT_S);
	ray->pla.y = plax * sin(-ROT_S) + ray->pla.y * cos(-ROT_S);
}

void	rot_left(t_ray *ray)
{
	double	dirx;
	double	plax;

	dirx = ray->dir.x;
	ray->dir.x = ray->dir.x * cos(ROT_S) - ray->dir.y * sin(ROT_S);
	ray->dir.y = dirx * sin(ROT_S) + ray->dir.y * cos(ROT_S);
	plax = ray->pla.x;
	ray->pla.x = ray->pla.x * cos(ROT_S) - ray->pla.y * sin(ROT_S);
	ray->pla.y = plax * sin(ROT_S) + ray->pla.y * cos(ROT_S);
}

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
		double cameraX = 2 * x / (double)(cub->rx) - 1; //x-coordinate in camera space
		double rayDirX = ray->dir.x + ray->pla.x * cameraX;
		double rayDirY = ray->dir.y + ray->pla.y * cameraX;
		//which box of the map we're in
		int mapX = (int)(ray->pos.x);
		int mapY = (int)(ray->pos.y);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
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
		//perform DDA
		int texNum = 0; //1 subtracted from it so that texture 0 can be used!

		int spr_hit = 0;
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (cub->map[mapX][mapY] == 'X')
			{
				printf("%d\n", ray->spr_nbr);
				ray->spr[ray->spr_nbr].x = (int)mapX + 0.5;
				ray->spr[ray->spr_nbr].y = (int)mapY + 0.5;
				spr_hit = 1;
				ray->spr_nbr = 1;
			}
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

			if (cub->map[mapX][mapY] == '1')
				hit = 1;
		}
		if (side == 0 && rayDirX > 0)
			texNum = 0;
		else if (side == 0 && rayDirX < 0)
			texNum = 1;
		else if (side == 1 && rayDirY < 0)
			texNum = 2;
		else
			texNum = 3;
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0) perpWallDist = (mapX - ray->pos.x + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - ray->pos.y + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(cub->ry / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + cub->ry / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + cub->ry / 2;
		if(drawEnd >= cub->ry)drawEnd = cub->ry - 1;

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = ray->pos.y + perpWallDist * rayDirY;
		else           wallX = ray->pos.x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(TEX_W));
		if(side == 0 && rayDirX > 0) texX = TEX_W - texX - 1;
		if(side == 1 && rayDirY < 0) texX = TEX_W - texX - 1;
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
			int color = ray->tex[texNum][TEX_H * texY + texX];

			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			mlx_pixel_draw(mlx, x, y, color);
			y++;
		}
		ray->z_buff[x] = perpWallDist; //perpendicular distance is used
		x++;
	}
	draw_sprite(cub, mlx, ray);
}


int		key_hook(int keycode, t_mlx *mlx)
{
	t_mlx	new;

	if (keycode == ESCAPE)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		ft_exit(EXIT_SUCCESS, mlx->cub, NULL);
	}
	mlx_destroy_image(mlx->mlx, mlx->img);
	new.img = mlx_new_image(mlx->mlx, mlx->pos.x, mlx->pos.y);
	new.addr = mlx_get_data_addr(new.img, &new.bpp, &new.len, &new.endian);
	if (keycode == MOVE_UP)
		mov_up(mlx->cub, mlx->ray);
	else if (keycode == MOVE_LEFT)
		mov_left(mlx->cub, mlx->ray);
	else if (keycode == MOVE_RIGHT)
		mov_right(mlx->cub, mlx->ray);
	else if (keycode == MOVE_DOWN)
		mov_down(mlx->cub, mlx->ray);
	else if (keycode == mlx->right)
		rot_right(mlx->ray);
	else if (keycode == mlx->left)
		rot_left(mlx->ray);
	draw(mlx->cub, &new, mlx->ray);
	mlx->img = new.img;
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (keycode);
}

void	raycasting(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	draw(cub, mlx, ray);
	mlx_hook(mlx->win, 2, 1L<<0, key_hook, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_loop(mlx->mlx);
}
