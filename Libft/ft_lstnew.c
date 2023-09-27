/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:18:18 by obelaizi          #+#    #+#             */
/*   Updated: 2023/09/27 16:49:14 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstnew(void *content)
{
	t_lst	*node;

	node = malloc(sizeof(t_lst));
	if (!node)
		return (0);
	node->data = content;
	node->next = 0;
	return (node);
}
