/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:11:33 by adeburea          #+#    #+#             */
/*   Updated: 2021/01/25 15:46:59 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_rgb	t_rgb;
struct			s_rgb
{
	int r;
	int g;
	int b;
};

typedef struct s_cub	t_cub;
struct			s_cub
{
	char id[9];
	char *r;
	char *no;
	char *so;
	char *we;
	char *ea;
	char *s;
	t_rgb f;
	t_rgb c;
};

#endif
