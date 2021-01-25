/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 00:13:32 by adeburea          #+#    #+#             */
/*   Updated: 2020/09/28 21:52:36 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*dst;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(dst = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	ft_memcpy(dst, s1, ft_strlen(s1) + 1);
	ft_strlcat(dst, s2, len);
	return (dst);
}
