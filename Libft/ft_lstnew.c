/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:18:18 by obelaizi          #+#    #+#             */
/*   Updated: 2023/02/13 18:16:26 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_line	*ft_lstnew(void *content)
{
	t_line	*node;

	node = malloc(sizeof(t_line));
	if (!node)
		return (0);
	node->data = content;
	node->next = 0;
	return (node);
}
