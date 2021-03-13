/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:49:17 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/13 12:43:44 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1100
#define screenHeight 800
#define w 1100
#define h 800


int worldMap[mapWidth][mapHeight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

double posX, posY;  //x and y start position
double dirX, dirY; //initial direction vector
double moveSpeed; //the constant value is in squares/second
double rotSpeed; //the constant value is in radians/second
double planeX, planeY;
int texture[8][4096];
t_mlx tex[8];

void	mlx_pixel_draw(t_mlx *mlx, int x, int y, int color)
{
	char    *dst;

	dst = mlx->addr + (y * mlx->len + x * (mlx->bpp / 8));
	*(unsigned int*)dst = color;
}

int		mlx_pixel_get(t_mlx *mlx, int x, int y)
{
	char	*color;

	color = mlx->addr + (x * mlx->len + y * (mlx->bpp / 8));
	return (*(unsigned int*)color);
}

void	mov_up(t_ray *ray)
{
	if (worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == 0)
		posX += dirX * moveSpeed;
	if (worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == 0)
		posY += dirY * moveSpeed;
}

void	mov_down(t_ray *ray)
{
	if (worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == 0)
		posX -= dirX * moveSpeed;
	if (worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == 0)
		posY -= dirY * moveSpeed;
}

void	mov_right(t_ray *ray)
{
	double oldDirX = dirX;
	dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
	dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
	double oldPlaneX = planeX;
	planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
	planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
}

void	mov_left(t_ray *ray)
{
	double oldDirX = dirX;
	dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
	dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
	double oldPlaneX = planeX;
	planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
	planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
}

void	draw(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	moveSpeed = 0.2; //the constant value is in squares/second
	rotSpeed = 0.1; //the 2d raycaster version of camera plane
	for(int x = 0; x < w; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)(w) - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)(posX);
		int mapY = (int)(posY);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
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
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)drawEnd = h - 1;

		//texturing calculations
		int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = posY + perpWallDist * rayDirY;
		else           wallX = posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(TEXW));
		if(side == 0 && rayDirX > 0) texX = TEXW - texX - 1;
		if(side == 1 && rayDirY < 0) texX = TEXW - texX - 1;
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * TEXH / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - h / 2 + lineHeight / 2) * step;

		for(int y = drawStart; y<drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (TEXH - 1) in case of overflow
			int texY = (int)texPos & (TEXH - 1);
			texPos += step;

			//int color = texture[texNum][TEXH * texY + texX];
			int color = ray->tex[side][TEXH * texY + texX];

			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			mlx_pixel_draw(mlx, x, y, color);
		}
	}
}

void put_texture_in_buffer(t_mlx *mlx)
{
	//DELETE
	int x = 0;
	int y = 0;
	int i = 0;
	while (i < 8)
	{
		x = 0;
		while (x < 64)
		{
			y = 0;
			while (y < 64)
			{
				texture[i][TEXW * x + y] = mlx_pixel_get(&tex[i], y, x);
				//printf("texture[i] = %d\n", texture[i][x + y]);
				y++;
			}
			x++;
		}
		i++;
	}
}

int		key_hook(int keycode, t_mlx *mlx)
{
	t_mlx	new;

	mlx_destroy_image(mlx->mlx, mlx->img);
	new.img = mlx_new_image(mlx->mlx, mlx->pos.x, mlx->pos.y);
	new.addr = mlx_get_data_addr(new.img, &new.bpp, &new.len, &new.endian);
	if (keycode == ESCAPE)
		exit(EXIT_SUCCESS);
	else if (keycode == UP)
		mov_up(mlx->ray);
	else if (keycode == DOWN)
		mov_down(mlx->ray);
	else if (keycode == RIGHT)
		mov_right(mlx->ray);
	else if (keycode == LEFT)
		mov_left(mlx->ray);
	draw(mlx->cub, &new, mlx->ray);
	mlx->img = new.img;
	mlx->addr = mlx_get_data_addr(new.img, &new.bpp, &new.len, &new.endian);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (keycode);
}

void	load_tex(t_mlx *mlx)
{
	//DELETE
	int		i;
	int x = 0;
	int y = 0;

	i = 0;
	tex[0].img = mlx_xpm_file_to_image
		(mlx->mlx, "./textures/eagle.xpm", &x, &y);
	tex[1].img = mlx_xpm_file_to_image
		(mlx->mlx, "./textures/redbrick.xpm", &x, &y);
	tex[2].img = mlx_xpm_file_to_image
		(mlx->mlx, "./textures/purplestone.xpm", &x, &y);
	tex[3].img = mlx_xpm_file_to_image
		(mlx->mlx, "./textures/greystone.xpm", &x, &y);
	tex[4].img = mlx_xpm_file_to_image
		(mlx->mlx, "./textures/bluestone.xpm", &x, &y);
	tex[5].img = mlx_xpm_file_to_image
		(mlx->mlx, "./textures/mossy.xpm", &x, &y);
	tex[6].img = mlx_xpm_file_to_image
		(mlx->mlx, "./textures/wood.xpm", &x, &y);
	tex[7].img = mlx_xpm_file_to_image
		(mlx->mlx, "./textures/colorstone.xpm", &x, &y);
	while (i < 8)
	{
		tex[i].addr = mlx_get_data_addr(tex[i].img,
			&tex[i].bpp, &tex[i].len, &tex[i].endian);
		i++;
	}
	put_texture_in_buffer(mlx);
}

void	raycasting(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	posX = 22, posY = 11.5;
	dirX = -1, dirY = 0; //initial direction vector
	planeX = 0, planeY = 0.66;

	load_tex(mlx);
	put_texture_in_buffer(mlx);
	draw(cub, mlx, ray);
	mlx_hook(mlx->win, 2, 1L<<0, key_hook, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_loop(mlx->mlx);
}
