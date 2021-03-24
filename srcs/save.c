/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:32:32 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/24 18:59:30 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	ft_header(t_mlx *recup, int fd)
{
	int	tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * recup->rx * recup->ry;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &recup->rx, 4);
	write(fd, &recup->ry, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &recup->data.bpp, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

void	ft_save(t_mlx *recup)
{
	int	fd;
	int	x;
	int	y;

	y = recup->ry;
	if ((fd = open("./image.bmp", O_CREAT | O_RDWR)) == -1)
		ft_error(recup, "Impossible de creer .bmp\n");
	ft_header(recup, fd);
	while (y >= 0)
	{
		x = 0;
		while (x < recup->rx)
		{
			write(fd, mlx_pixel_get(mlx, y, x), 4);
			x++;
		}
		y--;
	}
	//system("chmod 777 image.bmp");
	ft_error(recup, "Non jrigole --save ok\n");
}
