/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:01:00 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/14 15:15:23 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube3d.h"

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->len + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}

void	init_mlx(t_cub *cub, t_win *win)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, cub->rx, cub->ry, "Cube3D");
	win->img = mlx_new_image(mlx, cub->rx, cub->ry);
	win->addr = mlx_get_data_addr(win->img, &win->bpp, &win->len, &win->endian);
	my_mlx_pixel_put(win, 5, 5, 0x00FF5088);
	mlx_put_image_to_window(mlx, mlx_win, win->img, 0, 0);
	mlx_loop(mlx);
}

void	start_game(t_cub *cub)
{
	t_win	win;

	init_mlx(cub, &win);
	raycasting(cub, &win);
}
