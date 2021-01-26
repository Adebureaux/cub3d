/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:32:57 by adeburea          #+#    #+#             */
/*   Updated: 2021/01/26 01:29:17 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube3d.h"

t_cub	*init_cub(void)
{
	t_cub	*cub;

	cub = (t_cub*)malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->id = ft_split("R|NO|SO|WE|EA|S|F|C", '|');
	cub->r = NULL;
	cub->no = NULL;
	cub->so = NULL;
	cub->we = NULL;
	cub->ea = NULL;
	cub->s = NULL;
	cub->f.r = -1;
	cub->f.g = -1;
	cub->f.b = -1;
	cub->c.r = -1;
	cub->c.g = -1;
	cub->c.b = -1;
	return (cub);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_cub	*cub;

	cub = init_cub();
	free(cub->id);
	free(cub);
	return (0);
}
