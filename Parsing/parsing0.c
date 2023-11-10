/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:15:19 by obelaizi          #+#    #+#             */
/*   Updated: 2023/11/10 10:10:14 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	good_element(char **tmp, t_strp mp[7])
{
	int	i;

	i = 0;
	if (!tmp[0] || !tmp[0][0])
		return (1);
	while (tmp[i])
		i++;
	if (i > 2)
		return (ft_putstr_fd("Error\nToo many arguments\n", 2), 1);
	i = -1;
	while (++i < 6)
	{
		if (!ft_strcmp(tmp[0], mp[i].first))
		{
			if (mp[i].second)
				return (ft_putstr_fd("Error\nElement already set\n", 2), 0);
			return (mp[i].second = tmp[1], 1);
		}
	}
	return (printf("|%s|\n", tmp[0]), 0);
}

void	set_my_map(t_strp mp[6])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		mp[i].second = NULL;
		i++;
	}
	mp[0].first = "NO";
	mp[1].first = "SO";
	mp[2].first = "WE";
	mp[3].first = "EA";
	mp[4].first = "F";
	mp[5].first = "C";
}

bool	exist(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (true);
	return (false);
}

bool	start_map(char *line)
{
	int	i;

	if (!*line)
		return (false);
	i = 0;
	while (line[i] && (exist("NSEW01 ", line[i])))
		i++;
	if (!line[i])
		return (true);
	return (false);
}

char	**lst_tochar(t_lst *map)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_lstsize(map) + 1));
	ret[i] = NULL;
	i = 0;
	while (map)
	{
		ret[i] = map->data;
		i++;
		map = map->next;
	}
	return (ret);
}
