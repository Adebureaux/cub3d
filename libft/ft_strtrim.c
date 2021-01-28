/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 00:14:28 by adeburea          #+#    #+#             */
/*   Updated: 2020/11/21 18:38:21 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_set_isin(const char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i++] == c)
			return (1);
	}
	return (0);
}

char		*ft_strtrim(const char *s1, const char *set)
{
	char	*dst;
	size_t	start;
	size_t	len;

	start = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (ft_set_isin(set, s1[start]))
		start++;
	if (start != len)
	{
		while (ft_set_isin(set, s1[len - 1]))
			len--;
	}
	dst = ft_substr(s1, start, len - start);
	return (dst);
}
