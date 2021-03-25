/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 02:20:07 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/25 01:02:52 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	draw_wall_end(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall = ray->pos.y + ray->perp_wall_dst * ray->ray_dir.y;
	else
		ray->wall = ray->pos.x + ray->perp_wall_dst * ray->ray_dir.x;
	ray->wall -= floor((ray->wall));
	ray->tex_pos.x = (int)(ray->wall * (double)(TEX_W));
	if (ray->side == 0 && ray->ray_dir.x > 0)
		ray->tex_pos.x = TEX_W - ray->tex_pos.x - 1;
	if (ray->side == 1 && ray->ray_dir.y < 0)
		ray->tex_pos.x = TEX_W - ray->tex_pos.x - 1;
	ray->step_b = 1.0 * TEX_H / ray->line_h;
	ray->tex_b = (ray->draw_s - cub->ry / 2 + ray->line_h / 2) * ray->step_b;
	ray->y = ray->draw_s;
	while (ray->y < ray->draw_e)
	{
		ray->tex_pos.y = (int)ray->tex_b & (TEX_H - 1);
		ray->tex_b += ray->step_b;
		ray->color = ray->tex[ray->tex_nbr][TEX_H *
		ray->tex_pos.y + ray->tex_pos.x];
		if (ray->side == 1)
			ray->color = (ray->color >> 1) & 8355711;
		mlx_pixel_draw(mlx, ray->x, ray->y, ray->color);
		ray->y++;
	}
	ray->buf[ray->x] = ray->perp_wall_dst;
}

void	draw_wall_calc(t_cub *cub, t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir.x > 0)
		ray->tex_nbr = 0;
	else if (ray->side == 0 && ray->ray_dir.x < 0)
		ray->tex_nbr = 1;
	else if (ray->side == 1 && ray->ray_dir.y < 0)
		ray->tex_nbr = 2;
	else
		ray->tex_nbr = 3;
	if (ray->side == 0)
		ray->perp_wall_dst = (ray->map.x - ray->pos.x +
			(1 - ray->step.x) / 2) / ray->ray_dir.x;
	else
		ray->perp_wall_dst = (ray->map.y - ray->pos.y +
			(1 - ray->step.y) / 2) / ray->ray_dir.y;
	ray->line_h = (int)(cub->ry / ray->perp_wall_dst);
	ray->draw_s = -ray->line_h / 2 + cub->ry / 2;
	if (ray->draw_s < 0)
		ray->draw_s = 0;
	ray->draw_e = ray->line_h / 2 + cub->ry / 2;
	if (ray->draw_e >= cub->ry)
		ray->draw_e = cub->ry - 1;
}

void	draw_wall_hit(t_cub *cub, t_ray *ray)
{
	if (ray->side_dst.x <= ray->side_dst.y)
	{
		ray->side_dst.x += ray->delta_dst.x;
		ray->map.x += ray->step.x;
		ray->side = 0;
	}
	else
	{
		ray->side_dst.y += ray->delta_dst.y;
		ray->map.y += ray->step.y;
		ray->side = 1;
	}
	if (cub->map[ray->map.x][ray->map.y] == '1')
		ray->hit = 1;
}

void	draw_wall_dir(t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dst.x = (ray->pos.x - ray->map.x) * ray->delta_dst.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dst.x = (ray->map.x + 1.0 - ray->pos.x) * ray->delta_dst.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dst.y = (ray->pos.y - ray->map.y) * ray->delta_dst.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dst.y = (ray->map.y + 1.0 - ray->pos.y) * ray->delta_dst.y;
	}
}

void	draw_wall(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	ray->cam = 2 * ray->x / (double)(cub->rx) - 1;
	ray->ray_dir.x = ray->dir.x + ray->pla.x * ray->cam;
	ray->ray_dir.y = ray->dir.y + ray->pla.y * ray->cam;
	ray->map.x = (int)(ray->pos.x);
	ray->map.y = (int)(ray->pos.y);
	ray->hit = 0;
	ray->delta_dst.x = fabs(1 / ray->ray_dir.x);
	ray->delta_dst.y = fabs(1 / ray->ray_dir.y);
	draw_wall_dir(ray);
	while (ray->hit == 0)
		draw_wall_hit(cub, ray);
	draw_wall_calc(cub, ray);
	draw_wall_end(cub, mlx, ray);
}
