/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 23:26:06 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/17 00:32:37 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	free_tex(t_mlx *mlx, t_mlx *tex, int max)
{
	int		i;

	i = 0;
	while (i < max)
	{
		if (tex[i].img)
			mlx_destroy_image(mlx->mlx, tex[i].img);
		i++;
	}
	mlx_destroy_window(mlx->mlx, mlx->win);
	ft_exit(EXIT_FAILURE, mlx->cub, "Error: Failed to load texture\n");
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

void	load_more_texture(t_mlx *mlx, t_mlx *tex)
{
	tex[5].img = mlx_xpm_file_to_image(mlx->mlx, "./textures/wood.xpm",
		&tex[5].pos.x, &tex[5].pos.y);
	tex[6].img = mlx_xpm_file_to_image(mlx->mlx, "./textures/pillar.xpm",
		&tex[6].pos.x, &tex[6].pos.y);
	tex[7].img = mlx_xpm_file_to_image(mlx->mlx, "./textures/greenlight.xpm",
		&tex[7].pos.x, &tex[7].pos.y);
}

void	load_texture(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	int		i;
	t_mlx	tex[8];

	i = 0;
	tex[0].img = mlx_xpm_file_to_image(mlx->mlx, cub->so,
		&tex[0].pos.x, &tex[0].pos.y);
	tex[1].img = mlx_xpm_file_to_image(mlx->mlx, cub->no,
		&tex[1].pos.x, &tex[1].pos.y);
	tex[2].img = mlx_xpm_file_to_image(mlx->mlx, cub->we,
		&tex[2].pos.x, &tex[2].pos.y);
	tex[3].img = mlx_xpm_file_to_image(mlx->mlx, cub->ea,
		&tex[3].pos.x, &tex[3].pos.y);
	tex[4].img = mlx_xpm_file_to_image(mlx->mlx, cub->s,
		&tex[4].pos.x, &tex[4].pos.y);
	load_more_texture(mlx, tex);
	while (i < 8)
	{
		if (!tex[i].img)
			free_tex(mlx, tex, i);
		tex[i].addr = mlx_get_data_addr(tex[i].img,
			&tex[i].bpp, &tex[i].len, &tex[i].endian);
		bufferize_texture(mlx, &tex[i], ray->tex[i]);
		i++;
	}
}
