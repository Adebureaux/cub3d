/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:36:38 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/20 00:31:06 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	get_map(t_cub *cub)
{
	int		i;
	size_t	len;

	i = 1;
	len = sizeof(char*);
	cub->map = (void*)malloc(len * 2);
	if (!cub->map)
		ft_exit(EXIT_FAILURE, cub, "Error: Malloc break in init_cub\n");
	while (get_next_line(cub->fd, &cub->map[0]) > 0 && !cub->map[0][0])
		free(cub->map[0]);
	while (get_next_line(cub->fd, &cub->map[i]) > 0)
	{
		cub->map = ft_realloc(cub->map, len * (i + 1), len * (i + 2));
		i++;
	}
	free(cub->map[i]);
	cub->map[i] = NULL;
}

void	check_map(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (!ft_strchr(" 012NSEW", cub->map[i][j]))
				ft_exit(EXIT_FAILURE, cub, "Error: Wrong map\n");
			if (ft_strchr("NSEW", cub->map[i][j]))
			{
				if (cub->cp != 'X' && cub->cp)
					ft_exit(EXIT_FAILURE, cub, "Error: Wrong map\n");
				cub->cp = cub->map[i][j];
				cub->start.x = j;
				cub->start.y = i;
			}
			j++;
		}
		i++;
	}
	if (!ft_strchr("NSWE", cub->cp))
		ft_exit(EXIT_FAILURE, cub, "Error: Wrong map\n");
}

void	flood_check(t_cub *cub, int x, int y, int overflow)
{
	if (x < 0 || y < 0 || !cub->map[y][x] || cub->map[y][x] == ' ')
		ft_exit(EXIT_FAILURE, cub, "Error: Wrong map\n");
	if (overflow > 11591)
		ft_exit(EXIT_FAILURE, cub, "Error: Map is too big\n");
	if (cub->map[y][x] != '0' && cub->map[y][x] != '2')
		return ;
	if (cub->map[y][x] == 'O' || cub->map[y][x] == 'X')
		return ;
	if (cub->map[y][x] == '0')
		cub->map[y][x] = 'O';
	else if (cub->map[y][x] == '2')
		cub->map[y][x] = 'X';
	flood_check(cub, x + 1, y, overflow++);
	flood_check(cub, x - 1, y, overflow++);
	flood_check(cub, x, y + 1, overflow++);
	flood_check(cub, x, y - 1, overflow++);
}

void	display(t_cub *cub)
{
	int	i;

	i = 0;
	printf("\n______________DISPLAY______________\n");
	printf("rx = %d\n", cub->rx);
	printf("ry = %d\n", cub->ry);
	printf("no = %s\n", cub->no);
	printf("so = %s\n", cub->so);
	printf("we = %s\n", cub->we);
	printf("ea = %s\n", cub->ea);
	printf("s = %s\n", cub->s);
	printf("f = %d\n", cub->f);
	printf("c = %d\n", cub->c);
	printf("save = %d\n", cub->save);
	printf("pos cp = %c\n", cub->map[cub->start.y][cub->start.x]);
	printf("player pos x = %d\n", cub->start.x);
	printf("player pos y = %d\n", cub->start.y);
	printf("\n");
	if (cub->map)
	{
		while (cub->map[i])
			printf("%s\n", cub->map[i++]);
	}
	printf("_______________END_________________\n\n");
}

void	parse_map(t_cub *cub)
{
	get_map(cub);
	check_map(cub);
	cub->map[cub->start.y][cub->start.x] = '0';
	flood_check(cub, cub->start.x, cub->start.y, 0);
	cub->map[cub->start.y][cub->start.x] = cub->cp;
	display(cub);
	start_game(cub);
}
