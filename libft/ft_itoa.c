/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:09:45 by adeburea          #+#    #+#             */
/*   Updated: 2020/11/21 18:35:53 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_len(int n)
{
	int		len;

	len = 1;
	n < 0 ? len++ : 0;
	while ((n /= 10))
		len++;
	return (len);
}

char		*ft_itoa(int n)
{
	int			len;
	long int	nb;
	char		*dst;

	len = ft_itoa_len(n);
	if (!(dst = malloc(sizeof(char) * len + 1)))
		return (NULL);
	dst[len] = '\0';
	nb = n;
	if (nb < 0)
		nb = -nb;
	while (len--)
	{
		dst[len] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		dst[0] = '-';
	return (dst);
}
