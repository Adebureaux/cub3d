/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 23:26:06 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/18 18:35:14 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	draw_sprite(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	//DRAW SPRITE
	//1D ray->z_buff

	//arrays used to sort the sprites
	int spriteOrder[ray->spr_nbr];
	double spriteDistance[ray->spr_nbr];
	//SPRITE CASTING
	//sort sprites from far to close
	for(int i = 0; i < ray->spr_nbr; i++)
	{
	spriteOrder[i] = i;
	spriteDistance[i] = ((ray->pos.x - ray->spr[ray->spr_nbr].x) * (ray->pos.x - ray->spr[ray->spr_nbr].x) + (ray->pos.y - ray->spr[ray->spr_nbr].y) * (ray->pos.y - ray->spr[ray->spr_nbr].y)); //sqrt not taken, unneeded
	}
	//sortSprites(spriteOrder, spriteDistance, ray->spr_nbr);
	//after sorting the sprites, do the projection and draw them
		for(int i = 0; i < ray->spr_nbr; i++)
		{
		//translate sprite position to relative to camera
		double spriteX = ray->spr[ray->spr_nbr].x - ray->pos.x;
		double spriteY = ray->spr[ray->spr_nbr].y - ray->pos.y;

		//transform sprite with the inverse camera matrix
		// [ ray->pla.x   ray->dir.x ] -1                                       [ ray->dir.y      -ray->dir.x ]
		// [               ]       =  1/(ray->pla.x*ray->dir.y-ray->dir.x*ray->pla.y) *   [                 ]
		// [ ray->pla.y   ray->dir.y ]                                          [ -ray->pla.y  ray->pla.x ]

		double invDet = 1.0 / (ray->pla.x * ray->dir.y - ray->dir.x * ray->pla.y); //required for correct matrix multiplication

		double transformX = invDet * (ray->dir.y * spriteX - ray->dir.x * spriteY);
		double transformY = invDet * (-ray->pla.y * spriteX + ray->pla.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((cub->rx / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(cub->ry / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + cub->ry / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + cub->ry / 2;
		if(drawEndY >= cub->ry) drawEndY = cub->ry - 1;

		//calculate width of the sprite
		int spriteWidth = abs((int)(cub->ry / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= cub->rx) drawEndX = cub->rx - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_W / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < cub->rx && transformY < ray->z_buff[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
			int d = (y) * 256 - cub->ry * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
			int texY = ((d * TEX_H) / spriteHeight) / 256;
			int color = ray->tex[4][TEX_W * texY + texX]; //get current color from the texture
			if((color & 0x00FFFFFF) != 0)
			mlx_pixel_draw(mlx, stripe, y, color);
		}
	}
	}
}
