/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:11:33 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/14 15:14:42 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include "../libft/libft.h"
# include "../libmlx/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>

typedef struct s_rgb	t_rgb;
struct			s_rgb
{
	int			r;
	int			g;
	int			b;
};

typedef struct s_pos	t_pos;
struct			s_pos
{
	int			x;
	int			y;
};

typedef struct s_cub	t_cub;
struct			s_cub
{
	int			rx;
	int			ry;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	int			f;
	int			c;
	int			save;
	int			fd;
	char		cp;
	t_pos		start;
	char		*line;
	char		**map;
};

typedef struct  s_win {
	void        *img;
	char        *addr;
	int         bpp;
	int         len;
	int         endian;
}               t_win;

int				get_next_line(int fd, char **line);
void			ft_exit(int status, t_cub *cub, char *err);
void			ft_free(t_cub *cub, int i);
void			parse_file(char *av, t_cub *cub);
void			parse_map(t_cub *cub);
void			start_game(t_cub *cub);
void			raycasting(t_cub *cub, t_win *win);
#endif
