/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 00:13:40 by adeburea          #+#    #+#             */
/*   Updated: 2020/09/28 20:43:51 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t dst_len;
	size_t i;
	size_t j;

	dst_len = ft_strlen(dst);
	i = dst_len;
	j = 0;
	if (dstsize > dst_len)
	{
		while (j < dstsize - dst_len - 1 && src[j])
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
		return (ft_strlen(src) + dst_len);
	}
	else
		return (ft_strlen(src) + dstsize);
}
