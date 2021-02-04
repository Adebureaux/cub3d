/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:32:57 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/04 03:14:39 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube3d.h"

void	ft_free(t_cub *cub, int i)
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
		free(cub);
	}
}

void	ft_exit(int status, t_cub *cub, char *err)
{
	ft_free(cub, 0);
	if (status && !errno)
		ft_putstr_fd(err, 2);
	else if (status && errno)
		perror("Error");
	else
		ft_putstr_fd("Cube3d exited properly\n", 1);
	exit(status);
}

t_cub	*init_cub(void)
{
	t_cub	*cub;

	cub = (t_cub*)malloc(sizeof(t_cub));
	if (!cub)
		ft_exit(EXIT_FAILURE, cub, "Error: Malloc break in init_cub\n");
	cub->map = (void*)malloc(sizeof(void*));
	if (!cub->map)
		ft_exit(EXIT_FAILURE, cub, "Error: Malloc break in init_cub\n");
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
	cub->pos = '\0';
	cub->line = NULL;
	return (cub);
}

/* To delete (Only for verification prupose) */
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
	printf("save = %d\n\n", cub->save);
	if (cub->map)
	{
		while (cub->map[i])
			printf("%s\n", cub->map[i++]);
	}
	printf("_______________END_________________\n\n");
}

int		main(int ac, char **av)
{
	t_cub	*cub;

	if (ac > 3 || ac < 2)
		ft_exit(EXIT_FAILURE, NULL, "Error: Wrong number of arguments\n");
	cub = init_cub();
	if (ac == 3)
	{
		if (!ft_strcmp(av[2], "--save"))
			cub->save = 1;
		else
			ft_exit(EXIT_FAILURE, cub, "Error: Wrong second argument\n");
	}
	if (ft_strcmp(ft_strnstr(av[1], ".cub", ft_strlen(av[1])), ".cub"))
		ft_exit(EXIT_FAILURE, cub, "Error: Wrong map format\n");
	parse_file(av[1], cub);
	display(cub);
	ft_exit(EXIT_SUCCESS, cub, NULL);
}
