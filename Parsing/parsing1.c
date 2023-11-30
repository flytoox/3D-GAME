/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:10:20 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/22 15:57:06 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_itclosed(char **map, int n, int x, int y)
{
	if (x < 0 || y < 0 || x >= (int)ft_strlen(map[y]) || y >= n)
		return (false);
	if (map[y][x] == '1' || map[y][x] == 'x')
		return (true);
	if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'E' || map[y][x] == 'W')
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

	if (!map)
		return (false);
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
	if (!there_is_player(mp))
		return (ft_putstr_fd("Player error\n", 2), exit(1));
	else if (!check_closed(lst_tochar(map), ft_lstsize(map)))
		return (ft_putstr_fd("Error\nMap not closed\n", 2), exit(1));
	lmap.height = ft_lstsize(map) * TILE_SIZE;
	lmap.width = get_length(mp) * TILE_SIZE;
	display_3d_map(tmp, &lmap);
}

void	init_check(int *fd, char **line, char *map, t_strp *mp)
{
	*fd = open_map_file(map);
	*line = get_next_line(*fd);
	set_my_map(mp);
}

int	check_map(char *map)
{
	int		fd;
	char	*line;
	t_strp	mp[6];
	char	**tmp;

	if (check_file_extension(map))
		return (1);
	init_check(&fd, &line, map, mp);
	while (line)
	{
		if (start_map(line))
			break ;
		tmp = cust_split(line);
		free(line);
		line = get_next_line(fd);
		if (!good_element(tmp, mp))
			return (ft_putstr_fd("Error\nWrong element\n", 2), 1);
		free(tmp);
	}
	if (!line)
		return (ft_putstr_fd("Error\nNo map\n", 2), 1);
	if (check_map_last(mp))
		return (1);
	parsing_map(fd, line);
	return (0);
}
