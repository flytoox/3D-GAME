/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:10:20 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/11 16:13:54 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

bool	check_closed(char **map, int n)
{
	int		x;
	int		y;

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

int	get_length(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

void	parsing_map(int fd, char *line)
{
	t_lst	*map;
	char	**mp;
	char	**tmp;
	t_map	lmap;

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
	tmp = copy_map(mp);
	if (!check_closed(lst_tochar(map), ft_lstsize(map)))
		return (ft_putstr_fd("Error\nMap not closed\n", 2), exit(1));
	else
	{
		lmap.height = ft_lstsize(map) * TILE_SIZE;
		lmap.width = get_length(mp) * TILE_SIZE;
		display_map_on_screen(tmp, &lmap);
	}
}

int	check_map(char *map)
{
	int		fd;
	char	*line;
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
