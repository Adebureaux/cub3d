/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:01:00 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/17 00:29:56 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	resize_window(t_cub *cub, t_mlx *mlx)
{
	t_pos	res;

	res.x = cub->rx;
	res.y = cub->ry;
	mlx_get_screen_size(mlx->mlx, &cub->rx, &cub->ry);
	if (cub->rx > res.x)
		cub->rx = res.x;
	if (cub->ry > res.y)
		cub->ry = res.y;
	mlx->pos.x = cub->rx;
	mlx->pos.y = cub->ry;
}

void	set_position_2(t_cub *cub, t_ray *ray)
{
	if (cub->cp == 'E')
	{
		ray->dir.x = 0.01;
		ray->pla.x = 0.66;
		ray->dir.y = 0.99;
		ray->pla.y = 0.01;
	}
	else if (cub->cp == 'W')
	{
		ray->dir.x = -0.01;
		ray->pla.x = -0.66;
		ray->dir.y = -0.99;
		ray->pla.y = -0.01;
	}
}

void	set_position_1(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	ray->pos.x = cub->start.y + 0.5;
	ray->pos.y = cub->start.x + 0.5;
	mlx->right = RIGHT;
	mlx->left = LEFT;
	if (cub->cp == 'N')
	{
		ray->dir.x = -0.99;
		ray->pla.x = 0.01;
		ray->dir.y = 0;
		ray->pla.y = 0.66;
	}
	else if (cub->cp == 'S')
	{
		mlx->right = LEFT;
		mlx->left = RIGHT;
		ray->dir.x = 0.99;
		ray->pla.x = 0.01;
		ray->dir.y = 0;
		ray->pla.y = 0.66;
	}
	else
		set_position_2(cub, ray);
}

void	start_game(t_cub *cub)
{
	t_mlx	mlx;
	t_ray	ray;

	mlx.mlx = mlx_init();
	mlx.cub = cub;
	mlx.ray = &ray;
	resize_window(cub, &mlx);
	mlx.win = mlx_new_window(mlx.mlx, cub->rx, cub->ry, "Cube3D");
	mlx.img = mlx_new_image(mlx.mlx, cub->rx, cub->ry);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.len, &mlx.endian);
	load_texture(cub, &mlx, &ray);
	set_position_1(cub, &mlx, &ray);
	raycasting(cub, &mlx, &ray);
}
