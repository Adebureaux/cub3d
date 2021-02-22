/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:11:33 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/21 19:11:41 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../libmlx/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>
# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364
# define ESCAPE 65307
# define MOVE_SPEED 100
# define ROT_SPEED 100


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

typedef struct  s_mlx	t_mlx;
struct			s_mlx
{
	void		*cub;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			len;
	int			endian;
	int			color;
	t_pos		pos;
};

typedef struct  s_ray	t_ray;
struct			s_ray
{
	int x;
};

int				get_next_line(int fd, char **line);
void			ft_exit(int status, t_cub *cub, char *err);
void			ft_free(t_cub *cub, int i);
void			parse_file(char *av, t_cub *cub);
void			parse_map(t_cub *cub);
void			start_game(t_cub *cub);
void			raycasting(t_cub *cub, t_mlx *mlx, t_ray *ray);
int				key_hook(int keycode, t_mlx *mlx);
#endif
