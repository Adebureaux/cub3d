/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 00:14:35 by adeburea          #+#    #+#             */
/*   Updated: 2020/11/10 19:57:53 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char *dst;

	if (!s)
		return (NULL);
	len = ft_strlen(s) < len ? ft_strlen(s) : len;
	while (start-- && *s)
		s++;
	if (!(dst = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ft_strlcpy(dst, s, len + 1);
	return (dst);
}
