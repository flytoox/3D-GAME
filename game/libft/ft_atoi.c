/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:35:56 by obelaizi          #+#    #+#             */
/*   Updated: 2023/12/01 19:21:02 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>

int	ft_atoi(const char *str)
{
	int	ret;

	ret = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		ret = ret * 10 + *str - 48;
		str++;
	}
	if (ret <= 255 && ret >= 0)
		return (ret);
	return (-1);
}
