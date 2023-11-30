/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:26:12 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/20 15:28:50 by aait-mal         ###   ########.fr       */
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
	return (max);
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
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				player++;
			j++;
		}
		i++;
	}
	return (player == 1);
}

void	print_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
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
	while (map[i])
	{
		ret[i] = ft_strdup(map[i]);
		i++;
	}
	ret[i] = 0;
	return (ret);
}
