/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:49:17 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/19 20:57:55 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	draw_floor(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	int		y;

	y = 0;
	while (y < cub->ry)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		ray->ray_dir0.x = ray->dir.x - ray->pla.x;
		ray->ray_dir0.y = ray->dir.y - ray->pla.y;
		ray->ray_dir1.x = ray->dir.x + ray->pla.x;
		ray->ray_dir1.y = ray->dir.y + ray->pla.y;

		// Current y position compared to the center of the screen (the horizon)
		ray->p = y - cub->ry / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * cub->ry;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / ray->p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (ray->ray_dir1.x - ray->ray_dir0.x) / cub->rx;
		float floorStepY = rowDistance * (ray->ray_dir1.y - ray->ray_dir0.y) / cub->rx;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = ray->pos.x + rowDistance * ray->ray_dir0.x;
		float floorY = ray->pos.y + rowDistance * ray->ray_dir0.y;

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

		// floor
		ray->color = ray->tex[5][TEX_W * ty + tx];
		ray->color = (ray->color >> 1) & 8355711; // make a bit darker
		mlx_pixel_draw(mlx, x, y, ray->color);

		// ceiling (symmetrical, at cub->ry - y - 1 instead of y)
		ray->color = cub->c;
		mlx_pixel_draw(mlx, x, cub->ry - y - 1, ray->color);
		}
		y++;
	}
}

void	draw(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	draw_floor(cub, mlx, ray);
	ray->x = 0;
	while (ray->x < cub->rx)
	{
		draw_wall(cub, mlx, ray);
		ray->x++;
	}
	draw_sprite(cub, mlx, ray);
}

void	raycasting(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	draw(cub, mlx, ray);
	mlx_hook(mlx->win, 33, 1L << 17, quit, mlx);
	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx);
	mlx_loop_hook(mlx->mlx, key_hook, mlx);
	mlx_hook(mlx->win, 3, 1L << 1, key_release, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_loop(mlx->mlx);
}
