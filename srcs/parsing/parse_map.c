/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:36:38 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/04 03:22:26 by adeburea         ###   ########.fr       */
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
		while (cub->map[j])
		{
			if (!ft_strchr(" 012NSEW", cub->map[i][j]))
				ft_exit(EXIT_FAILURE, cub, "Error: Wrong map\n");
			if (ft_strchr("NSEW", cub->map[i][j]))
			{
				if (cub->pos)
					ft_exit(EXIT_FAILURE, cub, "Error: Wrong map\n");
				cub->pos = cub->map[i][j];
			}
			j++;
		}
		i++;
	}
}

void	parse_map(t_cub *cub)
{
	get_map(cub);
	valid_map(cub);
}
