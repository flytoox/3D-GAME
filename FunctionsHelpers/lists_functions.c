/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:39:49 by obelaizi          #+#    #+#             */
/*   Updated: 2023/09/27 16:41:07 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_lstadd_back(t_strct **lst, t_strct *new)
{
	t_strct	*check;

	if (!new)
		return ;
	if (!(*lst))
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	check = *lst;
	while (check->next)
		check = check->next;
	check->next = new;
}

void	ft_lstadd_front(t_strct **lst, t_strct *new)
{
	if (!new)
		return ;
	new ->next = *lst;
	*lst = new;
}

t_strct	*ft_lstnew(void *content)
{
	t_strct	*node;

	node = malloc(sizeof(t_strct));
	if (!node)
		return (0);
	node->data = content;
	node->next = 0;
	return (node);
}

int	ft_lstsize(t_strct *lst)
{
	t_strct	*i;
	int		count;

	if (!lst)
		return (0);
	count = 0;
	i = lst;
	while (i)
	{
		count++;
		i = i->next;
	}
	return (count);
}

void	ft_lstdelone(t_strct *lst)
{
	if (!lst)
		return ;
	free(lst->data);
	free(lst);
}
