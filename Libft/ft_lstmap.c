/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 05:52:14 by obelaizi          #+#    #+#             */
/*   Updated: 2023/09/27 16:49:14 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstmap(t_lst *lst, void *(*f)(void *), void (*del)(void *))
{
	t_lst	*node;
	t_lst	*begin;

	if (!lst || !f || !del)
		return (0);
	begin = 0;
	while (lst)
	{
		node = ft_lstnew(f(lst->data));
		if (!node)
			ft_lstclear(&begin);
		ft_lstadd_back(&begin, node);
		lst = lst->next;
	}
	return (begin);
}
