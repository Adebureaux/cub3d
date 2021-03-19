/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 02:20:07 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/19 13:05:05 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	mov_up(t_cub *cub, t_ray *ray)
{
	char	pos;

	pos = cub->map[(int)(ray->pos.x + ray->dir.x * MOV_S)][(int)(ray->pos.y)];
	if (pos == 'O' || pos == 'X')
		ray->pos.x += ray->dir.x * MOV_S;
	pos = cub->map[(int)(ray->pos.x)][(int)(ray->pos.y + ray->dir.y * MOV_S)];
	if (pos == 'O' || pos == 'X')
		ray->pos.y += ray->dir.y * MOV_S;
}

void	mov_down(t_cub *cub, t_ray *ray)
{
	char	pos;

	pos = cub->map[(int)(ray->pos.x - ray->dir.x * MOV_S)][(int)(ray->pos.y)];
	if (pos == 'O' || pos == 'X')
		ray->pos.x -= ray->dir.x * MOV_S;
	pos = cub->map[(int)(ray->pos.x)][(int)(ray->pos.y - ray->dir.y * MOV_S)];
	if (pos == 'O' || pos == 'X')
		ray->pos.y -= ray->dir.y * MOV_S;
}

void	mov_left(t_cub *cub, t_ray *ray)
{
	char	pos;

	pos = cub->map[(int)(ray->pos.x - ray->pla.x * MOV_S)]
					[(int)(ray->pos.y - ray->pla.y * MOV_S)];
	if (pos == 'O' || pos == 'X')
	{
		ray->pos.x -= ray->pla.x * MOV_S / 2;
		ray->pos.y -= ray->pla.y * MOV_S / 2;
	}
}

void	mov_right(t_cub *cub, t_ray *ray)
{
	char	pos;

	pos = cub->map[(int)(ray->pos.x + ray->pla.x * MOV_S)]
					[(int)(ray->pos.y - ray->pla.y * MOV_S)];
	if (pos == 'O' || pos == 'X')
	{
		ray->pos.x += ray->pla.x * MOV_S / 2;
		ray->pos.y += ray->pla.y * MOV_S / 2;
	}
}
