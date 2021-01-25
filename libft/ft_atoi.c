/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 00:10:28 by adeburea          #+#    #+#             */
/*   Updated: 2020/11/17 15:43:07 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int				i;
	int				sign;
	long long int	ret;

	i = 0;
	ret = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\f')
		i++;
	sign = str[i] == '-' ? -1 : 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		ret += str[i] - '0';
		ret *= ft_isdigit(str[i + 1]) ? 10 : 1;
		i++;
		if (ret < 0)
			return (sign == 1 ? -1 : 0);
	}
	return ((int)(ret * sign));
}
