/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:01:00 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/18 23:03:37 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	resize_window(t_cub *cub, t_mlx *mlx, t_pos *res)
{
	int	sizex = 1;
	int	sizey = 1;

	mlx_get_screen_size(mlx->mlx, &sizex, &sizey);
	if (cub->rx > sizex)
		res->x = sizex;
	if (cub->ry > sizey)
		res->y = sizey;
}

void	init_window(t_cub *cub, t_mlx *mlx)
{
	t_pos	res;

	mlx->mlx = mlx_init();
	perror("ERROR");
	resize_window(cub, mlx, &res);
	mlx->win = mlx_new_window(mlx->mlx, res.x, res.y, "Cube3D");
	mlx->img = mlx_new_image(mlx->mlx, res.x, res.y);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->len, &mlx->endian);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_loop(mlx->mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
}

void	start_game(t_cub *cub)
{
	t_mlx	mlx;

	init_window(cub, &mlx);
	//raycasting(cub, &win);
}
