/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:36:38 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/08 15:20:43 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cube3d.h"

void	get_map(t_cub *cub)
{
	int		i;
	size_t	len;

	i = 1;
	len = sizeof(char*);
	cub->map = (void*)malloc(len);
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

// Iterative form : https://www.codesdope.com/blog/article/making-a-queue-using-linked-list-in-c/
void	flood_check(t_cub *cub, char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y][x] || map[y][x] == ' ')
		ft_exit(EXIT_FAILURE, cub, "Error: Wrong map\n");
	if (map[y][x] != '0' && map[y][x] != '2')
		return ;
	if (map[y][x] == 'O' || map[y][x] == 'X')
		return ;
	if (map[y][x] == '0')
		map[y][x] = 'O';
	else if (map[y][x] == '2')
		map[y][x] = 'X';
	flood_check(cub, map, x + 1, y);
	flood_check(cub, map, x - 1, y);
	flood_check(cub, map, x, y + 1);
	flood_check(cub, map, x, y - 1);
}

void	parse_map(t_cub *cub)
{
	get_map(cub);
	check_map(cub);
	cub->map[cub->start.y][cub->start.x] = '0';
	flood_check(cub, cub->map, cub->start.x, cub->start.y);
	cub->map[cub->start.y][cub->start.x] = cub->cp;
}
