/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:11:33 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/01 10:52:05 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct s_rgb	t_rgb;
struct			s_rgb
{
	int		r;
	int		g;
	int		b;
};

typedef struct s_cub	t_cub;
struct			s_cub
{
	int		rx;
	int		ry;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int		f;
	int		c;
	int		save;
	char	*line;
};
void	ft_exit(int status, t_cub *cub, char *err);
int		get_next_line(int fd, char **line);
void	parse_file(char *av, t_cub *cub);
#endif
