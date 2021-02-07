/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:36:38 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/07 01:17:00 by adeburea         ###   ########.fr       */
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

t_pos	*pos_create(int x, int y)
{
	t_pos	*pos = malloc(sizeof(t_pos));

	pos->x = x;
	pos->y = y;
	return (pos);
}

void	pos_delete(t_pos **p)
{
	t_pos *pos;

	pos = *p;
	free(p);
	*p = NULL;
}

void	check_map(t_cub *cub)
{
	t_pos	*pos;
	t_list	*lst;

	pos = pos_create(cub->start.x, cub->start.y);
	while (lst->next)
	{
		lst = ft_lstnew(&pos);
		ft_lstadd_front(&lst, );

	}
}

void	parse_map(t_cub *cub)
{
	get_map(cub);
	valid_map(cub);
	check_map(cub);
}
