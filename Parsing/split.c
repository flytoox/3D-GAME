/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:25:24 by obelaizi          #+#    #+#             */
/*   Updated: 2023/09/26 22:39:56 by obelaizi         ###   ########.fr       */
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
	// if (ret[j - 1][ft_strlen(ret[j - 1]) - 1] == '\n')
	// 	ret[j - 1][ft_strlen(ret[j - 1]) - 1] = '\0';
	return (ret[j] = NULL, ret);
}
