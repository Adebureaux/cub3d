/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:37:18 by adeburea          #+#    #+#             */
/*   Updated: 2021/01/31 22:05:19 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cube3d.h"

void	parse_resolution(t_cub *cub)
{
	int		i;

	i = 0;
	if (ft_strncmp(cub->line, "R ", 2))
		ft_exit(EXIT_FAILURE, cub, "error: wrong resolution\n");
	i += 2;
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

void	parse_texture(char *cp, char **dst, t_cub *cub)
{
	int	len;

	len = ft_strlen(cp);
	if (ft_strncmp(cp, cub->line, len)
	|| ft_strncmp(cub->line + len, " ./", 3))
		ft_exit(EXIT_FAILURE, cub, "error: wrong texture\n");
	*dst = ft_strdup(cub->line + len + 1);
	if (!*dst || !*dst[0])
		ft_exit(EXIT_FAILURE, cub, "error: wrong texture\n");
}

void	parse_color(t_cub *cub)
{
	int	r;
	int	g;
	int	b;

	
	printf("line = %s\n", cub->line);
}

void	parse_desc(t_cub *cub, int n)
{
	if (n == 1)
		parse_resolution(cub);
	else if (n == 2)
		parse_texture("NO", &cub->no, cub);
	else if (n == 3)
		parse_texture("SO", &cub->so, cub);
	else if (n == 4)
		parse_texture("WE", &cub->we, cub);
	else if (n == 5)
		parse_texture("EA", &cub->ea, cub);
	else if (n == 6)
		parse_texture("S", &cub->s, cub);
	else if (n == 7)
		parse_color(cub);
}

//To delete
void	display(t_cub *cub)
{
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
	display(cub);
	close(fd);
}
