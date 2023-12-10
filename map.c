/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:25:51 by obelaizi          #+#    #+#             */
/*   Updated: 2023/12/10 17:29:59 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include <sys/fcntl.h>
#include <time.h>

#define MAP_WIDTH 60
#define MAP_HEIGHT 120

void	make_it_closed(char **map, int height, int width)
{
	int	x;
	int	y;

	x = -1;
	while (map[0][++x] && x < width)
		map[0][x] = '1';
	x = -1;
	while (map[height - 1][++x] && x < width)
		map[height - 1][x] = '1';
	y = -1;
	while (map[++y] && y < height)
	{
		map[y][0] = '1';
		map[y][width - 1] = '1';
	}
}

void	rand_map(char **map, int height, int width)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (rand() % 8 == 0)
				map[i][j] = '1';
			else
				map[i][j] = '0';
		}
	}
	make_it_closed(map, height, width);
}

void	player_pos(char **map, int height, int width)
{
	int	px;
	int	py;

	px = rand() % (width - 1);
	py = rand() % (height - 1);
	while (map[py][px] == '1')
	{
		px = rand() % (width - 1);
		py = rand() % (height - 1);
	}
	map[py][px] = 'N';
}

void	fill_file(char **map, int fd, int height, int width)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			ft_putchar_fd(map[i][j], fd);
		ft_putchar_fd('\n', fd);
	}
}

void	generate_map(void)
{
	char	**map;
	int		height;
	int		width;
	int		fd;

	srand((unsigned int)time(NULL));
	height = rand() % MAP_HEIGHT;
	width = rand() % MAP_WIDTH;
	map = malloc(sizeof(char *) * (height + 1));
	map[height] = NULL;
	for (int i = 0; i < height; i++)
	{
		map[i] = malloc(sizeof(char) * (width + 1));
		map[i][width] = '\0';
	}
	fd = open("mapTemp.cub", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	rand_map(map, height, width);
	player_pos(map, height, width);
	ft_putendl_fd("NO ./textures/wall.xpm", fd);
	ft_putendl_fd("SO ./textures/wall2.xpm", fd);
	ft_putendl_fd("WE ./textures/wall3.xpm", fd);
	ft_putendl_fd("EA ./textures/wall4.xpm", fd);
	ft_putendl_fd("C 0,255,255", fd);
	ft_putendl_fd("F 192,192,192", fd);
	fill_file(map, fd, height, width);
	free_tab(map);
}
