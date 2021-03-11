/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:11:33 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/11 15:02:17 by adeburea         ###   ########.fr       */
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
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MOVE_SPEED 1
# define ROT_SPEED 10

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
	void		*ray;
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

typedef struct  s_dpos	t_dpos;
struct			s_dpos
{
	double		x;
	double		y;
};

typedef struct  s_ray	t_ray;
struct			s_ray
{
	int			tex[5][4096];
	t_mlx		texture[5];
	t_dpos		pos;
	t_dpos		dir;
	t_dpos		plane;
	t_dpos		ray;
	t_dpos		side_dist;
	t_dpos		delta_dist;
	t_pos		map;
	t_pos		step;
	t_pos		tex_p;
	double		tex_pos;
	double		wall_dist;
	double		cam;
	double		wall;
	int			hit;
	int			side;
	int			step_p;
	int			line_h;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	int			color;
};

int				get_next_line(int fd, char **line);
void			ft_exit(int status, t_cub *cub, char *err);
void			parse_file(char *av, t_cub *cub);
void			parse_map(t_cub *cub);
void			start_game(t_cub *cub);
void			raycasting(t_cub *cub, t_mlx *mlx, t_ray *ray);
void			free_mlx(t_mlx *mlx, t_ray *ray);
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int				mlx_get_pixel_color(t_mlx *mlx, int x, int y);
#endif
