/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:01:00 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/16 04:07:08 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	free_tex(t_mlx *mlx, t_mlx tex[5], int i)
{
	while (i < 5)
	{
		if (tex[i].img)
			mlx_destroy_image(mlx->mlx, tex[i].img);
		i++;
	}
	mlx_destroy_window(mlx->mlx, mlx->win);
}

void	bufferize_texture(t_mlx *mlx, t_mlx *tex, int *dst)
{
	int		x;
	int		y;

	x = 0;
	while (x < TEX_W)
	{
		y = 0;
		while (y < TEX_H)
		{
			dst[TEX_H * x + y] = mlx_pixel_get(tex, x, y);
			y++;
		}
		x++;
	}
	mlx_destroy_image(mlx->mlx, tex->img);
}

void	load_texture(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	int		i;
	t_mlx	tex[5];

	i = 0;
	tex[0].img = mlx_xpm_file_to_image
		(mlx->mlx, cub->no, &tex[0].pos.x, &tex[0].pos.y);
	tex[1].img = mlx_xpm_file_to_image
		(mlx->mlx, cub->so, &tex[1].pos.x, &tex[1].pos.y);
	tex[2].img = mlx_xpm_file_to_image
		(mlx->mlx, cub->we, &tex[2].pos.x, &tex[2].pos.y);
	tex[3].img = mlx_xpm_file_to_image
		(mlx->mlx, cub->ea, &tex[3].pos.x, &tex[3].pos.y);
	tex[4].img = mlx_xpm_file_to_image
		(mlx->mlx, cub->s, &tex[4].pos.x, &tex[4].pos.y);
	while (i < 5)
	{
		if (!tex[i].img)
		{
			free_tex(mlx, tex, i);
			ft_exit(EXIT_FAILURE, cub, "Error: Failed to load texture\n");
		}
		tex[i].addr = mlx_get_data_addr(tex[i].img,
			&tex[i].bpp, &tex[i].len, &tex[i].endian);
		bufferize_texture(mlx, &tex[i], ray->tex[i]);
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
	raycasting(cub, &mlx, &ray);
}
