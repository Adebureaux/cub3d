/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 00:12:21 by adeburea          #+#    #+#             */
/*   Updated: 2020/09/28 20:44:16 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_s;
	size_t			i;

	ptr_s = (unsigned char*)s;
	i = -1;
	while (++i < n)
	{
		if (ptr_s[i] == (unsigned char)c)
			return ((void*)ptr_s + i);
	}
	return (NULL);
}
