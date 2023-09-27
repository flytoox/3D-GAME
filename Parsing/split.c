/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:25:24 by obelaizi          #+#    #+#             */
/*   Updated: 2023/09/27 15:51:26 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**cust_split(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**ret;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		k = i;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
			i++;
		if (i > k)
		{
			ret[j] = ft_substr(str, k, i - k);
			j++;
		}
	}
	return (ret[j] = NULL, ret);
}
