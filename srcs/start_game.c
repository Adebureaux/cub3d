/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:01:00 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/11 00:24:19 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	free_mlx(t_mlx *mlx, t_ray *ray)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		if (ray->texture[i].img)
			mlx_destroy_image(mlx->mlx, ray->texture[i].img);
		i++;
	}
	mlx_destroy_window(mlx->mlx, mlx->win);
}

void	load_texture(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	int		i;

	i = 0;
	ray->texture[0].img = mlx_xpm_file_to_image
		(mlx->mlx, cub->no, &ray->texture[0].pos.x, &ray->texture[0].pos.y);
	ray->texture[1].img = mlx_xpm_file_to_image
		(mlx->mlx, cub->so, &ray->texture[1].pos.x, &ray->texture[1].pos.y);
	ray->texture[2].img = mlx_xpm_file_to_image
		(mlx->mlx, cub->we, &ray->texture[2].pos.x, &ray->texture[2].pos.y);
	ray->texture[3].img = mlx_xpm_file_to_image
		(mlx->mlx, cub->ea, &ray->texture[3].pos.x, &ray->texture[3].pos.y);
	ray->texture[4].img = mlx_xpm_file_to_image
		(mlx->mlx, cub->s, &ray->texture[4].pos.x, &ray->texture[4].pos.y);
	while (i < 5)
	{
		if (!ray->texture[i].img)
		{
			free_mlx(mlx, ray);
			ft_exit(EXIT_FAILURE, cub, "Error: Failed to load texture\n");
		}
		ray->texture[i].addr = mlx_get_data_addr(ray->texture[i].img,
			&ray->texture[i].bpp, &ray->texture[i].len, &ray->texture[i].endian);
		i++;
	}
}

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

void	init_window(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	mlx->mlx = mlx_init();
	mlx->cub = cub;
	mlx->ray = ray;
	resize_window(cub, mlx);
	mlx->win = mlx_new_window(mlx->mlx, cub->rx, cub->ry, "Cube3D");
	mlx->img = mlx_new_image(mlx->mlx, cub->rx, cub->ry);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->len, &mlx->endian);
	load_texture(cub, mlx, ray);
}

void	start_game(t_cub *cub)
{
	t_mlx	mlx;
	t_ray	ray;

	init_window(cub, &mlx, &ray);
	raycasting(cub, &mlx, &ray);
}
