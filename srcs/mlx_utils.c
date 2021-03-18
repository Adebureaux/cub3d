/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 23:29:04 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/16 23:31:20 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	mlx_pixel_draw(t_mlx *mlx, int x, int y, int color)
{
	char    *dst;

	dst = mlx->addr + (y * mlx->len + x * (mlx->bpp / 8));
	*(unsigned int*)dst = color;
}

int		mlx_pixel_get(t_mlx *mlx, int x, int y)
{
	char	*color;

	color = mlx->addr + (x * mlx->len + y * (mlx->bpp / 8));
	return (*(unsigned int*)color);
}
