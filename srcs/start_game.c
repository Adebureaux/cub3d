/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:01:00 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/21 19:10:54 by adeburea         ###   ########.fr       */
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
	if (keycode == ESCAPE)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		ft_exit(EXIT_SUCCESS, mlx->cub, NULL);
	}
	return (keycode);
}

void	init_window(t_cub *cub, t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->cub = cub;
	resize_window(cub, mlx);
	mlx->win = mlx_new_window(mlx->mlx, cub->rx, cub->ry, "Cube3D");
	mlx->img = mlx_new_image(mlx->mlx, cub->rx, cub->ry);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->len, &mlx->endian);
	//mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	// mlx_hook(mlx->win, 2, 1L<<0, key_hook, mlx);
	// mlx_loop(mlx->mlx);
}

void	start_game(t_cub *cub)
{
	t_mlx	mlx;
	t_ray	ray;

	init_window(cub, &mlx);
	raycasting(cub, &mlx, &ray);
}
