/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:11:33 by adeburea          #+#    #+#             */
/*   Updated: 2021/01/26 01:10:54 by adeburea         ###   ########.fr       */
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

typedef struct s_cub	t_cub;
struct			s_cub
{
	int rx;
	int ry;
	char *no;
	char *so;
	char *we;
	char *ea;
	char *s;
	int f;
	int c;
	int save;
};
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strncpy(char *dst, char *src, size_t n);
#endif
