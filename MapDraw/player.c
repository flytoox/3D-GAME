/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:33:58 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/17 21:50:04 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	get_player_rotation_angle(char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N')
				return (3 * PI / 2);
			if (map[i][j] == 'S')
				return (PI / 2);
			if (map[i][j] == 'E')
				return (0);
			if (map[i][j] == 'W')
				return (PI);
			j++;
		}
		i++;
	}
	return (PI / 2);
}

void	init_player(t_player *player, char **map)
{
	player->radius = 3;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = get_player_rotation_angle(map);
	player->move_speed = 4.0;
	player->rotation_speed = 4 * (PI / 180);
}

void	reinit_player(t_player *player)
{
	player->walk_direction = 0;
	player->turn_direction = 0;
}
