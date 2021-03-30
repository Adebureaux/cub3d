/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:37:18 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/30 13:16:56 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	parse_resolution(t_cub *cub)
{
	int		i;

	i = 2;
	if (ft_strncmp(cub->line, "R ", 2))
		ft_exit(EXIT_FAILURE, cub, "Wrong resolution\n");
	while (cub->line[i] == ' ')
		i++;
	cub->rx = ft_atoi(cub->line + i);
	if (cub->rx < 1)
		ft_exit(EXIT_FAILURE, cub, "Wrong resolution\n");
	while (ft_isdigit(cub->line[i]))
		i++;
	if (cub->line[i++] != ' ')
		ft_exit(EXIT_FAILURE, cub, "Wrong resolution\n");
	while (cub->line[i] == ' ')
		i++;
	cub->ry = ft_atoi(cub->line + i);
	if (cub->ry < 1)
		ft_exit(EXIT_FAILURE, cub, "Wrong resolution\n");
	while (ft_isdigit(cub->line[i]))
		i++;
	if (cub->line[i])
		ft_exit(EXIT_FAILURE, cub, "Wrong resolution\n");
}

void	parse_texture(char **dst, t_cub *cub, int len)
{
	if (cub->line[len] != ' ')
		ft_exit(EXIT_FAILURE, cub, "Wrong texture\n");
	*dst = ft_strdup(cub->line + len + 1);
	if (!*dst || !*dst[0])
		ft_exit(EXIT_FAILURE, cub, "Wrong texture\n");
}

void	parse_color(int *c, t_cub *cub)
{
	int		i;
	t_rgb	rgb;

	i = 2;
	if (!ft_isdigit(cub->line[i]))
		ft_exit(EXIT_FAILURE, cub, "Wrong color\n");
	rgb.r = ft_atoi(&cub->line[i]);
	i += ft_nbrlen_base(rgb.r, 10);
	if (cub->line[i++] != ',' || rgb.r < 0 || rgb.r > 255)
		ft_exit(EXIT_FAILURE, cub, "Wrong color\n");
	if (!ft_isdigit(cub->line[i]))
		ft_exit(EXIT_FAILURE, cub, "Wrong color\n");
	rgb.g = ft_atoi(&cub->line[i]);
	i += ft_nbrlen_base(rgb.g, 10);
	if (cub->line[i++] != ',' || rgb.g < 0 || rgb.g > 255)
		ft_exit(EXIT_FAILURE, cub, "Wrong color\n");
	if (!ft_isdigit(cub->line[i]))
		ft_exit(EXIT_FAILURE, cub, "Wrong color\n");
	rgb.b = ft_atoi(&cub->line[i]);
	i += ft_nbrlen_base(rgb.b, 10);
	if (cub->line[i] || rgb.b < 0 || rgb.b > 255)
		ft_exit(EXIT_FAILURE, cub, "Wrong color\n");
	*c = (rgb.r << 16 | rgb.g << 8 | rgb.b);
}

void	parse_desc(t_cub *cub)
{
	if (!ft_strncmp(cub->line, "R ", 2) && cub->rx == -1 && cub->ry == -1)
		parse_resolution(cub);
	else if (!ft_strncmp("NO", cub->line, 2) && !cub->no)
		parse_texture(&cub->no, cub, 2);
	else if (!ft_strncmp("SO", cub->line, 2) && !cub->so)
		parse_texture(&cub->so, cub, 2);
	else if (!ft_strncmp("WE", cub->line, 2) && !cub->we)
		parse_texture(&cub->we, cub, 2);
	else if (!ft_strncmp("EA", cub->line, 2) && !cub->ea)
		parse_texture(&cub->ea, cub, 2);
	else if (!ft_strncmp("S", cub->line, 1) && !cub->s)
		parse_texture(&cub->s, cub, 1);
	else if (!ft_strncmp("F ", cub->line, 2) && cub->f == -1)
		parse_color(&cub->f, cub);
	else if (!ft_strncmp("C ", cub->line, 2) && cub->c == -1)
		parse_color(&cub->c, cub);
	else
		ft_exit(EXIT_FAILURE, cub, "Wrong description\n");
}

void	parse_file(char *av, t_cub *cub)
{
	int		n;
	int		ret;

	n = 0;
	ret = 1;
	cub->fd = open(av, O_RDONLY);
	while (n < 8)
	{
		ret = get_next_line(cub->fd, &cub->line);
		if (ret < 1)
			ft_exit(EXIT_FAILURE, cub, "Wrong map file\n");
		if (cub->line[0])
		{
			parse_desc(cub);
			n++;
		}
		free(cub->line);
		cub->line = NULL;
	}
	parse_map(cub);
}
