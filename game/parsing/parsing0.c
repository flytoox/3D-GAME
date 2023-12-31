/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:15:19 by obelaizi          #+#    #+#             */
/*   Updated: 2023/12/17 15:08:47 by obelaizi         ###   ########.fr       */
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
		return (ERR("Error\nToo many arguments\n", 2), exit(1), 0);
	i = -1;
	while (++i < 6)
	{
		if (!ft_strcmp(tmp[0], mp[i].first))
		{
			if (mp[i].second)
				return (ERR("Error\nElement already set\n", 2), exit(1), 0);
			return (mp[i].second = tmp[1], 1);
		}
	}
	return (0);
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
	int		j;

	if (!map)
		return (NULL);
	ret = malloc(sizeof(char *) * (ft_lstsize(map) + 1));
	if (!ret)
		return (exit(1), NULL);
	i = 0;
	while (map)
	{
		ret[i] = (char *)map->data;
		j = 0;
		i++;
		map = map->next;
	}
	return (ret[i] = NULL, ret);
}
