/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:26:12 by aait-mal          #+#    #+#             */
/*   Updated: 2023/12/12 16:54:12 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_length(char **map)
{
	int	i;
	int	j;
	int	max;

	if (!map)
		return (0);
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
	return (free(map), max);
}

int	there_is_player(char **map)
{
	int	i;
	int	j;
	int	player;

	if (!map)
		return (0);
	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				player++;
			j++;
		}
		i++;
	}
	return (free(map), player == 1);
}

int	get_map_height(char **map)
{
	int	i;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	**copy_map(char **map)
{
	char	**ret;
	int		i;

	if (!map)
		return (NULL);
	i = 0;
	ret = malloc(sizeof(char *) * (get_map_height(map) + 1));
	if (!ret)
		return (exit(1), NULL);
	while (map[i])
	{
		ret[i] = ft_strdup(map[i]);
		i++;
	}
	ret[i] = 0;
	return (free(map), ret);
}

void	fill_colors(int arr[], char **s)
{
	arr[0] = ft_atoi(s[0]);
	if (arr[0] == -1)
		return (ERR("Error\nThe colors should be between 0 and 255", 2),
			exit(1));
	arr[1] = ft_atoi(s[1]);
	if (arr[1] == -1)
		return (ERR("Error\nThe colors should be between 0 and 255", 2),
			exit(1));
	arr[2] = ft_atoi(s[2]);
	if (arr[2] == -1)
		return (ERR("Error\nThe colors should be between 0 and 255", 2),
			exit(1));
}
