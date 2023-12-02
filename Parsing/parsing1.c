/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:10:20 by aait-mal          #+#    #+#             */
/*   Updated: 2023/12/02 22:40:57 by obelaizi         ###   ########.fr       */
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

void	fill_colors(int arr[], char **s)
{
	arr[0] = ft_atoi(s[0]);
	if (arr[0] == -1)
		return (printf("The colors should be between 0 and 255"), exit(1));
	arr[1] = ft_atoi(s[1]);
	if (arr[1] == -1)
		return (printf("The colors should be between 0 and 255"), exit(1));
	arr[2] = ft_atoi(s[2]);
	if (arr[2] == -1)
		return (printf("The colors should be between 0 and 255"), exit(1));
}

void	set_colors(t_map *lmap, t_strp clrs[])
{
	char	**ret;
	int		i;

	ret = ft_split(clrs[4].second, ',');
	i = -1;
	while (ret[++i])
		;
	if (i != 3)
		return (printf("There is an error on the floor\n"), exit(1));
	fill_colors(lmap->clrs.flr, ret);
	free_tab(ret);
	ret = ft_split(clrs[5].second, ',');
	i = -1;
	while (ret[++i])
		;
	if (i != 3)
		return (printf("There is an error on the ceiling\n"), exit(1));
	fill_colors(lmap->clrs.ceilng, ret);
	free_tab(ret);
	lmap->clrs.no = clrs[0].second;
	lmap->clrs.so = clrs[1].second;
	lmap->clrs.we = clrs[2].second;
	lmap->clrs.ea = clrs[3].second;
}

void	parsing_map(int fd, char *line, t_strp clrs[])
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
	if (!check_closed(lst_tochar(map), ft_lstsize(map)))
		return (ft_putstr_fd("Error\nMap not closed\n", 2), exit(1));
	lmap.height = ft_lstsize(map) * TILE_SIZE;
	lmap.width = get_length(mp) * TILE_SIZE;
	set_colors(&lmap, clrs);
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
		free(tmp[0]);
		free(tmp);
	}
	if (!line)
		return (ft_putstr_fd("Error\nNo map\n", 2), 1);
	if (check_map_last(mp))
		return (1);
	return (parsing_map(fd, line, mp), 0);
}
