/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:36:38 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/08 03:12:48 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cube3d.h"

void	get_map(t_cub *cub)
{
	int		i;
	size_t	len;

	i = 1;
	len = sizeof(char*);
	while (get_next_line(cub->fd, &cub->map[i]) > 0)
	{
		cub->map = ft_realloc(cub->map, len * (i + 1), len * (i + 2));
		i++;
	}
	free(cub->map[i]);
	cub->map[i] = NULL;
}

void	valid_map(t_cub *cub)
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
				if (cub->cp)
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

void floodFillUtil(char **screen, int x, int y, char prevC, char newC)
{
	if (ft_strchr("NSEW", screen[x][y]))
		screen[x][y] = '0';
    // Base case
   if (x < 0 || y < 0 || !screen[x][y])
        return;
    if (screen[x][y] != prevC)
        return;
    if (screen[x][y] == newC)
        return;

    // Replace the color at (x, y)
    screen[x][y] = newC;

    // Recur for north, east, south and west
    floodFillUtil(screen, x+1, y, prevC, newC);
    floodFillUtil(screen, x-1, y, prevC, newC);
    floodFillUtil(screen, x, y+1, prevC, newC);
    floodFillUtil(screen, x, y-1, prevC, newC);
}

// It mainly finds the previous color on (x, y) and
// calls floodFillUtil()
void floodFill(char **screen, int x, int y, char newC)
{
    floodFillUtil(screen, y, x, '0', newC);
}

void	check_map(t_cub *cub)
{
	floodFill(cub->map, cub->start.x, cub->start.y, 'X');
	cub->map[cub->start.y][cub->start.x] = cub->cp;
}

void	parse_map(t_cub *cub)
{
	get_map(cub);
	valid_map(cub);
	check_map(cub);
}
