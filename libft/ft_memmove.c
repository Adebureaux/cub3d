/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 00:12:46 by adeburea          #+#    #+#             */
/*   Updated: 2020/11/14 19:17:23 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*ptr_dst;
	const unsigned char	*ptr_src;

	ptr_dst = (unsigned char*)dst;
	ptr_src = (unsigned char*)src;
	if (len < 1 || (!ptr_dst && !ptr_src))
		return (ptr_dst);
	if (dst > src)
		while (len--)
			*(ptr_dst + len) = *(ptr_src + len);
	else
		while (len--)
			*(ptr_dst++) = *(ptr_src++);
	return (dst);
}
