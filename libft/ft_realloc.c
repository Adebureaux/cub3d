/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:39:15 by adeburea          #+#    #+#             */
/*   Updated: 2021/02/02 15:44:38 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t ex, size_t size)
{
	void	*tmp;

	if (!ptr)
		return ((void*)malloc(size));
	tmp = (void*)malloc(size);
	if (!tmp)
		return (NULL);
	ft_memmove(tmp, ptr, ex);
	free(ptr);
	ptr = ((void*)malloc(size));
	if (!ptr)
		return (NULL);
	ft_memmove(ptr, tmp, size);
	free(tmp);
	return (ptr);
}
