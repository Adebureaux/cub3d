/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:57:39 by adeburea          #+#    #+#             */
/*   Updated: 2020/11/17 16:16:59 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *tmp;

	tmp = (*lst);
	if (lst)
	{
		while ((*lst) && del)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = tmp;
		}
	}
}
