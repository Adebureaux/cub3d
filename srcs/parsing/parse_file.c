/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:37:18 by adeburea          #+#    #+#             */
/*   Updated: 2021/01/28 13:56:23 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cube3d.h"

void	parse_file(t_cub *cub)
{
	char	*line;
	int		fd;

	fd = open("gnl.c", O_RDONLY);
	while ((get_next_line(fd, &line) > 0))
	{
		printf("%s\n", line);
		free(line);
	}
	(void)cub;
	close(fd);
}
