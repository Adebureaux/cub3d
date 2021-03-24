/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 02:20:07 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/24 18:03:12 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	mov_up(t_cub *cub, t_ray *ray)
{
	char	pos;

	pos = cub->map[(int)(ray->pos.x + ray->dir.x * MOV_S)][(int)(ray->pos.y)];
	if (pos == 'O')
		ray->pos.x += ray->dir.x * MOV_S;
	pos = cub->map[(int)(ray->pos.x)][(int)(ray->pos.y + ray->dir.y * MOV_S)];
	if (pos == 'O')
		ray->pos.y += ray->dir.y * MOV_S;
}

void	mov_down(t_cub *cub, t_ray *ray)
{
	char	pos;

	pos = cub->map[(int)(ray->pos.x - ray->dir.x * MOV_S)][(int)(ray->pos.y)];
	if (pos == 'O')
		ray->pos.x -= ray->dir.x * MOV_S;
	pos = cub->map[(int)(ray->pos.x)][(int)(ray->pos.y - ray->dir.y * MOV_S)];
	if (pos == 'O')
		ray->pos.y -= ray->dir.y * MOV_S;
}

void	mov_left(t_cub *cub, t_ray *ray)
{
	char	pos;

	pos = cub->map[(int)(ray->pos.x - ray->dir.y * MOV_S)][(int)ray->pos.y];
	if (pos == 'O')
		ray->pos.x -= ray->dir.y * MOV_S / 2;
	pos = cub->map[(int)ray->pos.x][(int)(ray->pos.y + ray->dir.x * MOV_S)];
	if (pos == 'O')
		ray->pos.y += ray->dir.x * MOV_S / 2;
}

void	mov_right(t_cub *cub, t_ray *ray)
{
	char	pos;

	pos = cub->map[(int)(ray->pos.x + ray->dir.y * MOV_S)][(int)ray->pos.y];
	if (pos == 'O')
		ray->pos.x += ray->dir.y * MOV_S / 2;
	pos = cub->map[(int)ray->pos.x][(int)(ray->pos.y - ray->dir.x * MOV_S)];
	if (pos == 'O')
		ray->pos.y -= ray->dir.x * MOV_S / 2;
}
