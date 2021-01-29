/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 12:50:33 by adeburea          #+#    #+#             */
/*   Updated: 2021/01/29 14:48:59 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cube3d.h"

void	parse_r_valid(t_cub *cub)
{
	int i;

	i = 0;
	if (cub->line[i++] != 'R')
		ft_exit(EXIT_FAILURE, cub, "error: wrong resolution\n");
	if (cub->line[i++] != ' ')
		ft_exit(EXIT_FAILURE, cub, "error: wrong resolution\n");
	while (ft_isdigit(cub->line[i]))
		i++;
	
}
