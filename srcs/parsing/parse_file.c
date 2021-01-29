/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:37:18 by adeburea          #+#    #+#             */
/*   Updated: 2021/01/29 16:41:13 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cube3d.h"

void	parse_r(t_cub *cub)
{
	int		i;

	i = 0;
	if (cub->line[i++] != 'R')
		ft_exit(EXIT_FAILURE, cub, "error: wrong resolution\n");
	if (cub->line[i++] != ' ')
		ft_exit(EXIT_FAILURE, cub, "error: wrong resolution\n");
	cub->rx = ft_atoi(cub->line + i);
	if (cub->rx < 1)
		ft_exit(EXIT_FAILURE, cub, "error: wrong resolution\n");
	while (ft_isdigit(cub->line[i]))
		i++;
	if (cub->line[i++] != ' ')
		ft_exit(EXIT_FAILURE, cub, "error: wrong resolution\n");
	cub->ry = ft_atoi(cub->line + i);
	if (cub->ry < 1)
		ft_exit(EXIT_FAILURE, cub, "error: wrong resolution\n");
	while (ft_isdigit(cub->line[i]))
		i++;
	if (cub->line[i])
		ft_exit(EXIT_FAILURE, cub, "error: wrong resolution\n");
}

void	parse_texture(t_cub *cub)
{
	int		i;

	i = 2;
	if (cub->line[i++] != ' ')
		ft_exit(EXIT_FAILURE, cub, "error: wrong north texture\n");
	if (cub->line[i] != '.')
		ft_exit(EXIT_FAILURE, cub, "error: wrong north texture\n");
	if (cub->line[i + 1] != '/')
		ft_exit(EXIT_FAILURE, cub, "error: wrong north texture\n");
	cub->no = ft_strdup(cub->line);
}

void	parse_desc(t_cub *cub, int n)
{
	if (n == 1)
		parse_r(cub);
	else if (n == 2)
	{
		// 26 lines
		// Place THIS in parse_texture(cub, 'N' 'O');
		if (cub->line[0] != 'N' && cub->line[1] != 'O')
			ft_exit(EXIT_FAILURE, cub, "error: wrong north texture\n");
		parse_texture(cub);
	}
	else if (n == 3)
	{
		if (cub->line[0] != 'S' && cub->line[1] != 'O')
			ft_exit(EXIT_FAILURE, cub, "error: wrong north texture\n");
		parse_texture(cub);
	}
	else if (n == 4)
	{
		if (cub->line[0] != 'W' && cub->line[1] != 'E')
			ft_exit(EXIT_FAILURE, cub, "error: wrong north texture\n");
		parse_texture(cub);
	}
	else if (n == 5)
	{
		if (cub->line[0] != 'E' && cub->line[1] != 'A')
			ft_exit(EXIT_FAILURE, cub, "error: wrong north texture\n");
		parse_texture(cub);
	}
}

void	parse_file(char *av, t_cub *cub)
{
	int		n;
	int		ret;
	int		fd;

	n = 1;
	ret = 1;
	fd = open(av, O_RDONLY);
	while (1)
	{
		ret = get_next_line(fd, &cub->line);
		if (!ret)
			break ;
		if (ret == -1)
			ft_exit(EXIT_FAILURE, cub, "error: wrong file descriptor\n");
		if (cub->line[0] != '\n')
			parse_desc(cub, n++);
		printf("%s\n", cub->line);
		free(cub->line);
	}
	close(fd);
}
