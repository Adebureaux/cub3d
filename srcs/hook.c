/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 02:20:07 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/19 03:19:39 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

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

int		key_hook(int keycode, t_mlx *mlx)
{
	t_mlx	new;

	if (keycode == ESCAPE)
		quit(mlx);
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
