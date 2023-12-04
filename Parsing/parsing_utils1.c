/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:46:49 by aait-mal          #+#    #+#             */
/*   Updated: 2023/12/04 21:08:20 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_file_extension(char *map)
{
	if (ft_strlen(map) >= 4
		&& ft_strncmp(map + ft_strlen(map) - 4, ".cub", 4) != 0)
		return (ft_putstr_fd("Error\nWrong file extension\n", 2), 1);
	return (0);
}

int	open_map_file(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nCan't open map\n", 2), 1);
	return (fd);
}

int	check_map_last(t_strp mp[6])
{
	int		i;

	i = -1;
	while (++i < 6) 
		if (!mp[i].second)
			return (ft_putstr_fd("Error\nMap should be the last\n", 2), 1);
	return (0);
}

bool	unkown_char(char **mp)
{
	int	i;
	int	j;

	j = -1;
	while (mp[++j])
	{
		i = -1;
		printf("|%s|\n", mp[j]);
		while (mp[j][++i])
			if (!ft_strchr("NSEW01 ", mp[j][i]))
				return (printf("Don't enter something sus on the map pls\n"),
					exit(1), true);
	}
	return (false);
}
