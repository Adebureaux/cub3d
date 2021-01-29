/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:53:48 by adeburea          #+#    #+#             */
/*   Updated: 2021/01/29 14:57:51 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(int n, char *base)
{
	int	size;

	size = ft_strlen(base);
	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', 1);
	}
	if (n >= size)
		ft_putnbr_base((int)(n / size), base);
	ft_putchar_fd(base[n % size], 1);
}
