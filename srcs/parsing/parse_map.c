/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:36:38 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/03 15:50:01 by adeburea         ###   ########.fr       */
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
	cub->map[i] = NULL;
}

void	parse_map(t_cub *cub)
{
	get_map(cub);
}
