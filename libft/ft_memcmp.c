/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 00:12:29 by adeburea          #+#    #+#             */
/*   Updated: 2020/11/13 15:47:18 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr_s1;
	const unsigned char	*ptr_s2;

	ptr_s1 = (unsigned char*)s1;
	ptr_s2 = (unsigned char*)s2;
	if (n < 1)
		return (0);
	while (--n)
	{
		if (*ptr_s1 != *ptr_s2)
			break ;
		ptr_s1++;
		ptr_s2++;
	}
	return ((*ptr_s1) - (*ptr_s2));
}
