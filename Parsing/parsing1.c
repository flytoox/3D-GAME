/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:10:20 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/10 12:57:52 by aait-mal         ###   ########.fr       */
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

void draw_filled_rectangle(void *mlx_ptr, void *win_ptr, int x, int y, int width, int height, int color)
{
    int i;
	int	j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            	mlx_pixel_put(mlx_ptr, win_ptr, x + j, y + i, 0xA9A9A9);
			else
            	mlx_pixel_put(mlx_ptr, win_ptr, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void draw_filled_circle(void *mlx_ptr, void *win_ptr, int x, int y, int radius, int color)
{
    int i, j;

    for (i = x - radius; i <= x + radius; i++)
    {
        for (j = y - radius; j <= y + radius; j++)
        {
            if ((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius)
            {
                mlx_pixel_put(mlx_ptr, win_ptr, i, j, color);
            }
        }
    }
}

void display_map_on_screen(char **map)
{
    int i;
    int j;
    t_mlx *mlx;
    int square_size;
    int player_radius = 8;  // Adjust the radius according to your preference

    mlx = malloc(sizeof(t_mlx));
    mlx->mlx_ptr = mlx_init();
    mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "CUB3D");
    square_size = WIDTH / ft_strlen(map[0]);
    i = 0;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '1')
                draw_filled_rectangle(mlx->mlx_ptr, mlx->win_ptr, j * square_size, i * square_size, square_size, square_size, 0x00FFFF);
            else if (map[i][j] == '0' || map[i][j] == 'N')
                draw_filled_rectangle(mlx->mlx_ptr, mlx->win_ptr, j * square_size, i * square_size, square_size, square_size, 0x00FFFFFF);
           	if (map[i][j] == 'N')
                draw_filled_circle(mlx->mlx_ptr, mlx->win_ptr, j * square_size + square_size / 2, i * square_size + square_size / 2, player_radius, 0x00FF0000);
            j++;
        }
        i++;
    }
    mlx_loop(mlx->mlx_ptr);
}

char	**copy_map(char **map)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_strlen(map[0]) + 1));
	while (map[i])
	{
		ret[i] = ft_strdup(map[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

bool	check_closed(char **map, int n)
{
	int		x;
	int		y;
	char	**tmp;

	y = 0;
	tmp = copy_map(map);
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
	display_map_on_screen(tmp);
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
	if (!check_closed(lst_tochar(map), ft_lstsize(map)))
		return (ft_putstr_fd("Error\nMap not closed\n", 2), exit(1));
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
