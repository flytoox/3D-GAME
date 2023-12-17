/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:25:24 by obelaizi          #+#    #+#             */
/*   Updated: 2023/12/12 16:55:21 by obelaizi         ###   ########.fr       */
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
	j = -1;
	ret = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	if (!ret)
		return (exit(1), NULL);
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		k = i;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
			i++;
		if (i > k)
		{
			ret[++j] = ft_substr(str, k, i - k);
			if (!ret[j])
				return (free_tab(ret), exit(1), NULL);
		}
	}
	return (ret[++j] = NULL, ret);
}
