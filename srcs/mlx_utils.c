/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 23:29:04 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/24 17:10:55 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int		quit(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	ft_exit(EXIT_SUCCESS, mlx->cub, NULL);
	return (1);
}

int		quit_error(t_mlx *mlx, char *err)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	ft_exit(EXIT_FAILURE, mlx->cub, err);
	return (1);
}

void	mlx_pixel_draw(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->len + x * (mlx->bpp / 8));
	*(unsigned int*)dst = color;
}

int		mlx_pixel_get(t_mlx *mlx, int x, int y)
{
	char	*color;

	color = mlx->addr + (x * mlx->len + y * (mlx->bpp / 8));
	return (*(unsigned int*)color);
}
