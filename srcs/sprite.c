/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 23:26:06 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/25 03:07:59 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	sort_sprite(t_dpos *arr, double *cmp, int n)
{
	int		i;
	int		j;
	double	temp;
	t_dpos	tmp;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (cmp[j] < cmp[j + 1])
			{
				temp = cmp[j];
				cmp[j] = cmp[j + 1];
				cmp[j + 1] = temp;
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	init_sprite(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	int		i;

	i = 0;
	if (cub->spr_nbr > 100)
		quit_error(mlx, "Error: Too many sprites\n");
	while (i < cub->spr_nbr)
	{
		ray->spr_dst[i] = ((ray->pos.x - cub->spr[i].x)
		* (ray->pos.x - cub->spr[i].x) + (ray->pos.y - cub->spr[i].y)
		* (ray->pos.y - cub->spr[i].y));
		i++;
	}
	sort_sprite(cub->spr, ray->spr_dst, cub->spr_nbr);
	ray->i = 0;
}

void	first_loop(t_cub *cub, t_ray *ray)
{
	ray->sprite.x = cub->spr[ray->i].x - ray->pos.x + 0.5;
	ray->sprite.y = cub->spr[ray->i].y - ray->pos.y + 0.5;
	ray->inv_det = 1.0 / (ray->pla.x * ray->dir.y -
					ray->dir.x * ray->pla.y);
	ray->transform.x = ray->inv_det * (ray->dir.y * ray->sprite.x -
						ray->dir.x * ray->sprite.y);
	ray->transform.y = ray->inv_det * (-ray->pla.y * ray->sprite.x +
						ray->pla.x * ray->sprite.y);
	ray->sprite_screen = (int)((cub->rx / 2) * (1 + ray->transform.x /
							ray->transform.y));
	ray->sprite_height = abs((int)(cub->ry / (ray->transform.y)));
	ray->draw_start.y = -ray->sprite_height / 2 + cub->ry / 2;
	if (ray->draw_start.y < 0)
		ray->draw_start.y = 0;
	ray->draw_end.y = ray->sprite_height / 2 + cub->ry / 2;
	if (ray->draw_end.y >= cub->ry)
		ray->draw_end.y = cub->ry - 1;
	ray->sprite_width = abs((int)(cub->ry / (ray->transform.y)));
	ray->draw_start.x = -ray->sprite_width / 2 + ray->sprite_screen;
	if (ray->draw_start.x < 0)
		ray->draw_start.x = 0;
	ray->draw_end.x = ray->sprite_width / 2 + ray->sprite_screen;
	if (ray->draw_end.x >= cub->rx)
		ray->draw_end.x = cub->rx - 1;
	ray->stripe = ray->draw_start.x;
}

void	draw_sprite(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	init_sprite(cub, mlx, ray);
	while (ray->i < cub->spr_nbr)
	{
		first_loop(cub, ray);
		while (ray->stripe < ray->draw_end.x)
		{
			ray->tex_p.x = (int)(256 * (ray->stripe - (-ray->sprite_width
				/ 2 + ray->sprite_screen)) * TEX_W / ray->sprite_width) / 256;
			if (ray->transform.y > 0 && ray->stripe > 0 && ray->stripe <
					cub->rx && ray->transform.y < ray->buf[ray->stripe])
				ray->y = ray->draw_start.y;
			while (ray->y < ray->draw_end.y)
			{
				ray->d = (ray->y) * 256 - cub->ry *
							128 + ray->sprite_height * 128;
				ray->tex_p.y = ((ray->d * TEX_H) / ray->sprite_height) / 256;
				ray->color = ray->tex[4][TEX_W * ray->tex_p.y + ray->tex_p.x];
				if ((ray->color & 0x00FFFFFF) != 0)
					mlx_pixel_draw(mlx, ray->stripe, ray->y, ray->color);
				ray->y++;
			}
			ray->stripe++;
		}
		ray->i++;
	}
}
