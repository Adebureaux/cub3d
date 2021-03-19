/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 23:26:06 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/19 02:10:48 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

// A function to implement bubble sort
void	sort_sprite(t_dpos *arr, double *comp, int n)
{
    int i, j;
	t_dpos tmp;

    for (i = 0; i < n-1; i++)
	{
    // Last i elements are already in place
    for (j = 0; j < n-i-1; j++)
	{
        if (comp[j] < comp[j+1])
		{
			tmp = arr[j+1];
			arr[j+1] = arr[j];
			arr[j] = tmp;
		}
	}
	}
}

void	draw_sprite(t_cub *cub, t_mlx *mlx, t_ray *ray)
{
	//DRAW SPRITE
	//1D ray->z_buff
	//arrays used to sort the sprites
	//SPRITE CASTING
	//sort sprites from far to close
	for(int i = 0; i < cub->spr_nbr; i++)
	{
		ray->spr_dst[i] = ((ray->pos.x - cub->spr[i].x)
		* (ray->pos.x - cub->spr[i].x) + (ray->pos.y - cub->spr[i].y)
		* (ray->pos.y - cub->spr[i].y));
	}
	sort_sprite(cub->spr, ray->spr_dst, cub->spr_nbr);
	//sortSprites(spriteOrder, spriteDistance, ray->spr_nbr);
	//after sorting the sprites, do the projection and draw them

		for(int i = 0; i < cub->spr_nbr; i++)
		{
		//translate sprite position to relative to camera
		double spriteX = cub->spr[i].x - ray->pos.x + 0.5;
		double spriteY = cub->spr[i].y - ray->pos.y + 0.5;

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
			if(transformY > 0 && stripe > 0 && stripe < cub->rx && transformY < ray->buf[stripe])
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
