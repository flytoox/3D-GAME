/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:10:20 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/10 11:04:16 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_itclosed(char **map, int n, int x, int y)
{
	if (x < 0 || y < 0 || x >= (int)ft_strlen(map[y]) || y >= n)
		return (false);
	if (map[y][x] == '1' || map[y][x] == 'x' || map[y][x] == 'n')
		return (true);
	if (map[y][x] == '0' || map[y][x] == 'N')
	{
		if (map[y][x] == 'N')
			map[y][x] = 'n';
		else
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
    int i, j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            mlx_pixel_put(mlx_ptr, win_ptr, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void	display_map_on_screen(char **map)
{
	int		i;
	int		j;
	t_mlx	*mlx;
	int square_size;

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
				draw_filled_rectangle(mlx->mlx_ptr, mlx->win_ptr, j * square_size, i * square_size, square_size, square_size, 0x00FF0000);
			else if (map[i][j] == 'x')
				draw_filled_rectangle(mlx->mlx_ptr, mlx->win_ptr, j * square_size, i * square_size, square_size, square_size, 0x00FFFFFF);
			else if (map[i][j] == 'n')
				draw_filled_rectangle(mlx->mlx_ptr, mlx->win_ptr, j * square_size, i * square_size, square_size, square_size, 0x0000FF00);
			j++;
		}
		i++;
	}
	mlx_loop(mlx->mlx_ptr);
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
	display_map_on_screen(map);
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
