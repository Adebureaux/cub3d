/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:49:17 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/11 15:02:45 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64
#define screenWidth 800
#define screenHeight 800
#define w 800
#define h 800
# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364
# define ESCAPE 65307


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
int buffer[screenHeight][screenWidth];

t_mlx tex[8];

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char    *dst;

	dst = mlx->addr + (y * mlx->len + x * (mlx->bpp / 8));
	*(unsigned int*)dst = color;
}

int		mlx_get_pixel_color(t_mlx *mlx, int x, int y)
{
	char	*color;

	color = mlx->addr + (y * mlx->len + x * (mlx->bpp / 8));
	return (*(unsigned int*)color);
}

void	mov_up()
{
	if (worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == 0)
		posX += dirX * moveSpeed;
	if (worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == 0)
		posY += dirY * moveSpeed;
}

void	mov_down()
{
	if (worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == 0)
		posX -= dirX * moveSpeed;
	if (worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == 0)
		posY -= dirY * moveSpeed;
}

void	mov_right()
{
	double oldDirX = dirX;
	dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
	dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
	double oldPlaneX = planeX;
	planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
	planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
}

void	mov_left()
{
	double oldDirX = dirX;
	dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
	dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
	double oldPlaneX = planeX;
	planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
	planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
}

void	draw(t_mlx *mlx)
{
	moveSpeed = 0.5; //the constant value is in squares/second
	rotSpeed = 0.3; //the 2d raycaster version of camera plane
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
		int texX = (int)(wallX * (double)(texWidth));
		if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - h / 2 + lineHeight / 2) * step;

		for(int y = drawStart; y<drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = texture[texNum][texHeight * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
			//buffer[y][x] = color;
			my_mlx_pixel_put(mlx, x, y, color);
		}
		//drawBuffer(img);
		//for(int y = 0; y < h; y++) for(int x = 0; x < w; x++) buffer[y][x] = 0; //clear the buffer instead of cls()
	}
}

void put_texture_in_buffer(t_mlx *mlx)
{
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
				texture[i][texWidth * x + y] = mlx_get_pixel_color(&tex[i], y, x);
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
	t_mlx new;

	mlx_destroy_image(mlx->mlx, mlx->img);
	new.img = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
	new.addr = mlx_get_data_addr(new.img, &new.bpp, &new.len, &new.endian);
	if (keycode == ESCAPE)
		exit(EXIT_SUCCESS);
	else if (keycode == UP)
		mov_up();
	else if (keycode == DOWN)
		mov_down();
	else if (keycode == RIGHT)
		mov_right();
	else if (keycode == LEFT)
		mov_left();
	draw(&new);
	mlx->img = new.img;
	mlx->addr = mlx_get_data_addr(new.img, &new.bpp, &new.len, &new.endian);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (keycode);
}

void	load_tex(t_mlx *mlx)
{
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

void	raycasting(t_cub *cub, t_mlx *todo, t_ray *ray)
{
	t_mlx  mlx;

	posX = 22, posY = 11.5;
	dirX = -1, dirY = 0; //initial direction vector
	planeX = 0, planeY = 0.66;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, screenWidth, screenHeight, "Raycaster");
	mlx.img = mlx_new_image(mlx.mlx, screenWidth, screenHeight);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.len, &mlx.endian);
	load_tex(&mlx);
	put_texture_in_buffer(&mlx);
	draw(&mlx);
	mlx_hook(mlx.win, 2, 1L<<0, key_hook, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
}
