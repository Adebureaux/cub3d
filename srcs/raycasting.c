/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:49:17 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/23 01:49:31 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	mlx_pixel_draw(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->len + x * (mlx->bpp / 8));
	*(unsigned int*)dst = color;
}

int		mlx_get_pixel_color(t_mlx *mlx, int x, int y)
{
	char	*color;

	color = mlx->addr + (y * mlx->len + x * (mlx->bpp / 8));
	return (*(unsigned int*)color);
}

void	raycasting(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	ray->pos.x = cub->start.x;
	ray->pos.y = cub->start.y;
	ray->dir.x = -1.0;
	ray->dir.y = 0.0;
	ray->plane.x = 0.0;
	ray->plane.y = 0.66;

	for (int x = 0; x < cub->rx; x++)
	{
		ray->cam = 2 * x / (double)cub->rx - 1;
		ray->ray.x = ray->dir.x + ray->plane.x * ray->cam;
		ray->ray.y = ray->dir.y + ray->plane.y * ray->cam;

		ray->map.x = (int)ray->pos.x;
		ray->map.y = (int)ray->pos.y;

		ray->delta_dist.x = fabs(1 / ray->dir.x);
		ray->delta_dist.y = fabs(1 / ray->dir.y);

		ray->hit = 0;

		if (ray->dir.x < 0)
		{
			ray->step.x = -1;
			ray->side_dist.x = (ray->pos.x - ray->map.x) * ray->delta_dist.x;
		}
		else
		{
			ray->step.x = 1;
			ray->side_dist.x = (ray->map.x + 1.0 - ray->pos.x) * ray->delta_dist.x;
		}
		if (ray->dir.y < 0)
		{
			ray->step.y = -1;
			ray->side_dist.y = (ray->pos.y - ray->map.y) * ray->delta_dist.y;
		}
		else
		{
			ray->step.y = 1;
			ray->side_dist.y = (ray->map.y + 1.0 - ray->pos.y) * ray->delta_dist.y;
		}
		while (ray->hit == 0)
		{
			if (ray->side_dist.x < ray->side_dist.y)
			{
				ray->side_dist.x += ray->delta_dist.x;
				ray->map.x += ray->step.x;
				ray->side = 0;
			}
			else
			{
				ray->side_dist.y += ray->delta_dist.y;
				ray->map.y += ray->step.y;
				ray->side = 1;
			}
			//printf("%c\n", cub->map[ray->map.x][ray->map.y]);
			if (cub->map[ray->map.y][ray->map.x] == '1')
				ray->hit = 1;
		}
		if (ray->side == 0)
			ray->wall_dist = (ray->map.x - ray->pos.x + (1 - ray->step.x) / 2) / ray->dir.x;
		else
			ray->wall_dist = (ray->map.y - ray->pos.y + (1 - ray->step.y) / 2) / ray->dir.y;

		ray->line_h = (int)(cub->ry / ray->wall_dist);

		ray->draw_start = (ray->line_h * -1) / 2 + cub->ry / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_h / 2 + cub->ry / 2;
		if (ray->draw_end >= cub->ry)
			ray->draw_end = cub->ry - 1;

		ray->tex_num = 0;//cub->map[ray->map.x][ray->map.y] - 1;

		if (ray->side == 0)
			ray->wall = ray->pos.y + ray->wall_dist * ray->dir.y;
		else
			ray->wall = ray->pos.x + ray->wall_dist * ray->dir.x;
		ray->wall -= floor(ray->wall);

		ray->tex_p.x = (int)(ray->wall * (double)TEX_WIDTH);
		if (ray->side == 0 && ray->dir.x > 0)
			ray->tex_p.x = TEX_WIDTH - ray->tex_p.x - 1;
		if (ray->side == 1 && ray->dir.y < 0)
			ray->tex_p.x = TEX_WIDTH - ray->tex_p.x - 1;

		ray->step_p = 1.0 * TEX_HEIGHT / ray->line_h;

		ray->tex_pos = (ray->draw_start - cub->ry / 2 + ray->line_h / 2) * ray->step_p;
		printf("start = %d\n", ray->draw_start);
		printf("end = %d\n", ray->draw_end);
		for (int y = ray->draw_start; y < ray->draw_end; y++)
		{
			printf("color = %d\n", ray->color);
			ray->tex_p.y = (int)ray->tex_pos & (TEX_HEIGHT - 1);
			ray->tex_pos += ray->step_p;
			ray->color = mlx_get_pixel_color(&ray->tex[ray->tex_num], ray->tex_p.y, ray->tex_p.x);
			//ray->color = ray->tex[ray->tex_num][TEX_HEIGHT * ray->tex_p.y + ray->tex_p.x];
			// if (ray->side == 1)
			// 	ray->color = (ray->color >> 1) & 8355711;
			mlx_pixel_draw(mlx, x, y, ray->color);
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_hook(mlx->win, 2, 1L<<0, key_hook, mlx);
	mlx_loop(mlx->mlx);
    //drawBuffer(buffer[0]);
    //for(int y = 0; y < cub->ry; y++) for(int x = 0; x < cub->rx; x++) buffer[y][x] = 0; //clear the buffer instead of cls()

    //speed modifiers
    // double moveSpeed = MOVE_SPEED * 5.0; //the constant value is in squares/second
    // double rotSpeed = ROT_SPEED * 3.0; //the constant value is in radians/second

    // readKeys();
    // //move forward if no wall in front of you
    // if(keyDown(SDLK_UP))
    // {
    //   if(worldMap[int(ray->pos.x + dirX * moveSpeed)][int(ray->pos.y)] == false) ray->pos.x += dirX * moveSpeed;
    //   if(worldMap[int(ray->pos.x)][int(ray->pos.y + dirY * moveSpeed)] == false) ray->pos.y += dirY * moveSpeed;
    // }
    // //move backwards if no wall behind you
    // if(keyDown(SDLK_DOWN))
    // {
    //   if(worldMap[int(ray->pos.x - dirX * moveSpeed)][int(ray->pos.y)] == false) ray->pos.x -= dirX * moveSpeed;
    //   if(worldMap[int(ray->pos.x)][int(ray->pos.y - dirY * moveSpeed)] == false) ray->pos.y -= dirY * moveSpeed;
    // }
    // //rotate to the right
    // if(keyDown(SDLK_RIGHT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    //   dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    //   planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    // }
    // //rotate to the left
    // if(keyDown(SDLK_LEFT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
    //   dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    //   planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    // }
    // if(keyDown(SDLK_ESCAPE))
    // {
    //   break;
    // }
}
