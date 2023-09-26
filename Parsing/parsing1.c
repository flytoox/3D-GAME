/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:15:19 by obelaizi          #+#    #+#             */
/*   Updated: 2023/09/26 22:44:24 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	good_element(char **tmp, t_strp mp[7])
{
	int	i;

	i = 0;
	if (!tmp[0][0])
		return (1);
	while (tmp[i])
		i++;
	if (i > 2)
		return (ft_putstr_fd("Error\nToo many arguments\n", 2), 1);
	i = -1;
	while (++i < 7)
	{
		puts("good?");
		if (!ft_strcmp(tmp[0], mp[i].first))
		{
			if (mp[i].second)
				return (ft_putstr_fd("Error\nElement already set\n", 2), 0);
			return (mp[i].second = tmp[1], 1);
		}
	}
	return (0);
}

void	set_my_map(t_strp mp[7])
{
	int	i;

	i = 0;
	while (i < 7)
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
	mp[6].first = "MAP";
}

bool	start_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (false);
		i++;
	}
	if (!i)
		return (false);
	printf("MAP START\n");
	return (true);
}

int	check_map(char *map)
{
	int		fd;
	char	*line;
	int		ret;
	t_strp	mp[7];
	char	**tmp;

	if (ft_strlen(map) >= 4
		&& ft_strncmp(map + ft_strlen(map) - 4, ".cub", 4) != 0)
		return (ft_putstr_fd("Error\nWrong file extension\n", 2), 1);
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nCan't open map\n", 2), 1);
	line = get_next_line(fd);
	set_my_map(mp);
	while (line)
	{
		if (start_map(line))
			break ;
		tmp = cust_split(line);
		line = get_next_line(fd);
		if (!good_element(tmp, mp))
			return (ft_putstr_fd("Error\nWrong element\n", 2), 1);
	}
	if (!line)
		return (ft_putstr_fd("Error\nNo map\n", 2), 1);
	return (0);
}
