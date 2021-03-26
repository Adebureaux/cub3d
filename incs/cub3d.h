/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:11:33 by adeburea          #+#    #+#             */
/*   Updated: 2021/03/26 14:26:28 by adeburea         ###   ########.fr       */
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
# define MOVE_UP 119
# define MOVE_LEFT 97
# define MOVE_DOWN 115
# define MOVE_RIGHT 100
# define LEFT 65361
# define RIGHT 65363
# define ESCAPE 65307
# define MOV_S 0.12
# define ROT_S 0.035
# define TEX_W 64
# define TEX_H 64

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

typedef struct s_dpos	t_dpos;
struct			s_dpos
{
	double		x;
	double		y;
};

typedef struct s_fpos	t_fpos;
struct			s_fpos
{
	float		x;
	float		y;
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
	t_dpos		spr[100];
	int			spr_nbr;
};

typedef struct s_mlx	t_mlx;
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
	t_pos		pos;
	int			right;
	int			left;
	int			move_up;
	int			move_left;
	int			move_right;
	int			move_down;
	int			rot_left;
	int			rot_right;
	int			left_dir;
	int			right_dir;
};

typedef struct s_ray	t_ray;
struct			s_ray
{
	int			tex[8][4096];
	double		buf[3000];
	double		spr_dst[100];
	t_dpos		pos;
	t_dpos		dir;
	t_dpos		pla;
	int			side;
	int			tex_nbr;
	double		perp_wall_dst;
	double		cam;
	t_dpos		ray_dir;
	t_pos		map;
	t_dpos		side_dst;
	t_dpos		delta_dst;
	t_pos		step;
	int			hit;
	int			line_h;
	int			draw_s;
	int			draw_e;
	double		wall;
	t_pos		tex_pos;
	double		step_b;
	double		tex_b;
	int			color;
	t_fpos		ray_dir0;
	t_fpos		ray_dir1;
	float		posz;
	float		row_dst;
	t_fpos		fl_step;
	t_fpos		floor;
	t_pos		cell;
	t_pos		t;
	int			p;
	int			x;
	int			y;
	int			i;
	int			d;
	t_dpos		sprite;
	double		inv_det;
	t_dpos		transform;
	int			sprite_screen;
	int			sprite_height;
	t_pos		draw;
	t_pos		draw_start;
	t_pos		draw_end;
	int			sprite_width;
	int			stripe;
	t_pos		tex_p;
};

int				get_next_line(int fd, char **line);
void			ft_exit(int status, t_cub *cub, char *err);
void			parse_file(char *av, t_cub *cub);
void			parse_map(t_cub *cub);
void			start_game(t_cub *cub);
void			load_texture(t_cub *cub, t_mlx *mlx, t_ray *ray);
void			raycasting(t_cub *cub, t_mlx *mlx, t_ray *ray);
void			mlx_pixel_draw(t_mlx *mlx, int x, int y, int color);
int				mlx_pixel_get(t_mlx *mlx, int x, int y);
int				key_press(int keycode, t_mlx *mlx);
int				key_release(int keycode, t_mlx *mlx);
int				key_hook(t_mlx *mlx);
void			mov_up(t_cub *cub, t_ray *ray);
void			mov_down(t_cub *cub, t_ray *ray);
void			mov_left(t_cub *cub, t_ray *ray);
void			mov_right(t_cub *cub, t_ray *ray);
int				quit(t_mlx *mlx);
int				quit_error(t_mlx *mlx, char *err);
void			draw(t_cub *cub, t_mlx *mlx, t_ray *ray);
void			draw_sprite(t_cub *cub, t_mlx *mlx, t_ray *ray);
void			draw_wall(t_cub *cub, t_mlx *mlx, t_ray *ray);
void			save(t_cub *cub, t_mlx *mlx);

#endif
