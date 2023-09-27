/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:15:19 by obelaizi          #+#    #+#             */
/*   Updated: 2023/09/27 17:44:40 by obelaizi         ###   ########.fr       */
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

bool	is_itclosed(char **map, int n, int x, int y)
{
	if (x < 0 || y < 0 || x >= (int)ft_strlen(map[y]) || y >= n)
		return (false);
	if (map[y][x] == '1' || map[y][x] == 'x')
		return (true);
	if (map[y][x] == '0' || map[y][x] == 'N')
	{
		map[y][x] = 'x';
		if (is_itclosed(map, n, x + 1, y)
			&& is_itclosed(map, n, x - 1, y)
			&& is_itclosed(map, n, x, y + 1)
			&& is_itclosed(map, n, x, y - 1))
			return (true);
	}
	return (false);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

bool	check_closed(char **map, int n)
{
	int	x;
	int	y;
	
	y = 0;
	print_map(map);
	printf("\n\n");
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' && !is_itclosed(map, n, x, y))
				return (print_map(map), 0);
			x++;
		}
		y++;
	}
	return (1);
}

void	parsing_map(int fd, char *line)
{
	t_lst	*map;
	char	**mp;
	
	map = NULL;
	while (line && *line)
	{
		ft_lstadd_back((t_lst **)&map, ft_lstnew((void *)line));
		line = get_next_line(fd);
	}
	while (line && !*line)
		line = get_next_line(fd);
	if (line)
		return (ft_putstr_fd("Error\nMap should be the last;)\n", 2), exit(1));
	mp = lst_tochar(map);
	// while (map)
	// {
	// 	printf("%s\n", map->data);
	// 	map = map->next;
	// }
	if (!check_closed(lst_tochar(map), ft_lstsize(map)))
		return (ft_putstr_fd("Error\nMap not closed\n", 2), exit(1));
}

int	check_map(char *map)
{
	int		fd;
	char	*line;
	int		ret;
	t_strp	mp[6];
	char	**tmp;
	int		i;

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
	i = -1;
	while (++i < 6) 
		if (!mp[i].second)
			return (ft_putstr_fd("Error\nMap should be the last\n", 2), 1);
	parsing_map(fd, line);
	return (0);
}
