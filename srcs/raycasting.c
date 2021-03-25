/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:49:17 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/25 14:03:54 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	init_floor(t_cub *cub, t_ray *ray)
{
	ray->ray_dir0.x = ray->dir.x - ray->pla.x;
	ray->ray_dir0.y = ray->dir.y - ray->pla.y;
	ray->ray_dir1.x = ray->dir.x + ray->pla.x;
	ray->ray_dir1.y = ray->dir.y + ray->pla.y;
	ray->p = ray->y - cub->ry / 2;
	ray->posz = 0.5 * cub->ry;
	ray->row_dst = ray->posz / ray->p;
	ray->fl_step.x = ray->row_dst *
						(ray->ray_dir1.x - ray->ray_dir0.x) / cub->rx;
	ray->fl_step.y = ray->row_dst *
						(ray->ray_dir1.y - ray->ray_dir0.y) / cub->rx;
	ray->floor.x = ray->pos.x + ray->row_dst * ray->ray_dir0.x;
	ray->floor.y = ray->pos.y + ray->row_dst * ray->ray_dir0.y;
}

void	draw_floor(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	init_floor(cub, ray);
	ray->x = 0;
	while (ray->x++ < cub->rx)
	{
		ray->cell.x = (int)(ray->floor.x);
		ray->cell.y = (int)(ray->floor.y);
		ray->t.x = (int)(TEX_W * ray->floor.x - ray->cell.x) & TEX_W - 1;
		ray->t.y = (int)(TEX_H * ray->floor.y - ray->cell.y) & TEX_H - 1;
		ray->floor.x += ray->fl_step.x;
		ray->floor.y += ray->fl_step.y;
		ray->color = ray->tex[5][TEX_W * ray->t.y + ray->t.x];
		ray->color = (ray->color >> 1) & 8355711;
		mlx_pixel_draw(mlx, ray->x, ray->y, ray->color);
		ray->color = cub->c;
		mlx_pixel_draw(mlx, ray->x, cub->ry - ray->y - 1, ray->color);
	}
}

void	draw_life(t_cub *cub, t_mlx *mlx)
{
	int		h;
	int		i;
	int		j;

	h = cub->rx * 90 / 100;
	i = cub->rx - h;
	while (i < h)
	{
		j = cub->ry * 90 / 100;
		while (j < cub->ry)
		{
			mlx_pixel_draw(mlx, i, j, 0X00FF0000);
			j++;
		}
		i++;
	}
}

void	draw(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	ray->y = 0;
	while (ray->y < cub->ry)
	{
		draw_floor(cub, mlx, ray);
		ray->y++;
	}
	ray->x = 0;
	while (ray->x < cub->rx)
	{
		draw_wall(cub, mlx, ray);
		ray->x++;
	}
	draw_sprite(cub, mlx, ray);
	draw_life(cub, mlx);
}

void	raycasting(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	draw(cub, mlx, ray);
	if (cub->save)
		save(cub, mlx);
	mlx_hook(mlx->win, 33, 1L << 17, quit, mlx);
	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx);
	mlx_loop_hook(mlx->mlx, key_hook, mlx);
	mlx_hook(mlx->win, 3, 1L << 1, key_release, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_loop(mlx->mlx);
}
