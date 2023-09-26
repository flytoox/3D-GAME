/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 05:52:14 by obelaizi          #+#    #+#             */
/*   Updated: 2023/01/27 20:09:42 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_line	*ft_lstmap(t_line *lst, void *(*f)(void *), void (*del)(void *))
{
	t_line	*node;
	t_line	*begin;

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
