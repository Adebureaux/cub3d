/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:01:00 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/20 01:33:17 by adeburea         ###   ########.fr       */
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
}

int		key_hook(int keycode, t_mlx *mlx)
{
	printf("%d\n", keycode);
	if (keycode == ESCAPE)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		ft_exit(EXIT_SUCCESS, mlx->cub, NULL);
	}
	return (keycode);
}

int		mlx_verline(t_cub *cub, t_mlx *mlx)
{
	if (mlx->pos.y2 < mlx->pos.y1)
	{
		mlx->pos.y1 += mlx->pos.y2;
		mlx->pos.y2 = mlx->pos.y1 - mlx->pos.y2;
		mlx->pos.y1 -= mlx->pos.y2;
	}
	if (mlx->pos.y2 < 0 || mlx->pos.y1 >= cub->ry
		|| cub->rx < 0 || mlx->pos.y2 >= cub->ry)
		return (0);
	if (mlx->pos.y1 < 0)
		mlx->pos.y1 = 0;
	if (mlx->pos.y2 >=  cub->ry)
		mlx->pos.y2 =  cub->rx - 1;
	while (mlx->pos.y1 < mlx->pos.y2)
	{
		mlx_pixel_put(mlx->mlx, mlx->win, cub->rx, mlx->pos.y1, mlx->color);
		mlx->pos.y1++;
	}
	return (1);
}

void	init_window(t_cub *cub, t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->cub = cub;
	resize_window(cub, mlx);
	mlx->win = mlx_new_window(mlx->mlx, cub->rx, cub->ry, "Cube3D");
	mlx->img = mlx_new_image(mlx->mlx, cub->rx, cub->ry);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->len, &mlx->endian);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	start_game(t_cub *cub)
{
	t_mlx	mlx;

	init_window(cub, &mlx);
}
