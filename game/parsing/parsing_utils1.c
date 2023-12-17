/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:46:49 by aait-mal          #+#    #+#             */
/*   Updated: 2023/12/17 15:11:11 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_file_extension(char *map)
{
	if (WIN_WIDTH != 1280 || WIN_HEIGHT != 720)
		return (ERR("Error\nResolution must be 1280x720\n", 2), 1);
	if (ft_strlen(map) >= 4
		&& ft_strncmp(map + ft_strlen(map) - 4, ".cub", 4))
		return (ERR("Error\nWrong file extension\n", 2), 1);
	return (0);
}

int	open_map_file(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (ERR("Error\nCan't open map\n", 2), exit(1), 1);
	return (fd);
}

int	check_map_last(t_strp mp[6])
{
	int	i;

	i = -1;
	while (++i < 6)
		if (!mp[i].second)
			return (ERR("Error\nMap should be the last\n", 2), 1);
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
		while (mp[j][++i])
			if (!ft_strchr("NSEW01 ", mp[j][i]))
				return (ERR("Error\nYou can only use these \"NSEW01 \"\n",
						2), exit(1), true);
	}
	return (free(mp), false);
}

bool	is_itclosed(char **map, int n, int x, int y)
{
	if (x < 0 || y < 0 || y >= n || x >= (int)ft_strlen(map[y]))
		return (false);
	if (map[y][x] == '1' || map[y][x] == 'x')
		return (true);
	if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'E' || map[y][x] == 'W')
	{
		map[y][x] = 'x';
		if (is_itclosed(map, n, x + 1, y) && is_itclosed(map, n, x - 1, y)
			&& is_itclosed(map, n, x, y + 1) && is_itclosed(map, n, x, y - 1))
			return (true);
	}
	return (false);
}
