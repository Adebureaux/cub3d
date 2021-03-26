/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:32:57 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/26 14:12:25 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	free_cub(t_cub *cub, int i)
{
	if (cub)
	{
		if (cub->no)
			free(cub->no);
		if (cub->so)
			free(cub->so);
		if (cub->we)
			free(cub->we);
		if (cub->ea)
			free(cub->ea);
		if (cub->s)
			free(cub->s);
		if (cub->line)
			free(cub->line);
		if (cub->map)
		{
			while (cub->map[i])
				free(cub->map[i++]);
			free(cub->map);
		}
		close(cub->fd);
	}
}

void	ft_exit(int status, t_cub *cub, char *err)
{
	free_cub(cub, 0);
	if (status)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(err, 2);
	}
	else
		ft_putstr_fd("Cub3d exited properly\n", 1);
	exit(status);
}

void	init_cub(t_cub *cub)
{
	cub->rx = -1;
	cub->ry = -1;
	cub->no = NULL;
	cub->so = NULL;
	cub->we = NULL;
	cub->ea = NULL;
	cub->s = NULL;
	cub->f = -1;
	cub->c = -1;
	cub->save = 0;
	cub->cp = 'X';
	cub->line = NULL;
	cub->map = NULL;
	cub->spr_nbr = 0;
}

int		main(int ac, char **av)
{
	t_cub	cub;

	if (ac > 3 || ac < 2)
		ft_exit(EXIT_FAILURE, NULL, "Wrong number of arguments\n");
	init_cub(&cub);
	if (ac == 3)
	{
		if (!ft_strcmp(av[2], "--save"))
			cub.save = 1;
		else
			ft_exit(EXIT_FAILURE, &cub, "Wrong second argument\n");
	}
	if (ft_strcmp(ft_strnstr(av[1], ".cub", ft_strlen(av[1])), ".cub"))
		ft_exit(EXIT_FAILURE, &cub, "Wrong map format\n");
	parse_file(av[1], &cub);
	ft_exit(EXIT_SUCCESS, &cub, NULL);
}
