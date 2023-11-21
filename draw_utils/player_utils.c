/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:33:58 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/21 22:13:50 by aait-mal         ###   ########.fr       */
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
	player->side_movement = 0;
	player->rotation_angle = get_player_rotation_angle(map);
	player->move_speed = 3;
	player->rotation_speed = 3 * (PI / 180);
}

void	reinit_player(t_player *player)
{
	player->walk_direction = 0;
	player->turn_direction = 0;
}

int	is_there_wall_at(double x, double y, t_map *lmap)
{
	int	map_index_x;
	int	map_index_y;
	int	ret;

	map_index_x = floor(x / TILE_SIZE);
	map_index_y = floor(y / TILE_SIZE);
	if (map_index_x < 0 || map_index_x >= lmap->width
		|| map_index_y < 0 || map_index_y >= lmap->height)
		ret = 1;
	else
		ret = lmap->map[map_index_y][map_index_x] == '1';
	return (ret);
}

void	set_coordinates(double *new_x, double *new_y,
	t_map *lmap, int side_movement)
{
	double	rotation_angle;

	rotation_angle = lmap->player->rotation_angle;
	if (side_movement == 1)
	{
		*new_x = lmap->player->x + cos(rotation_angle - PI / 2)
			* lmap->player->move_speed;
		*new_y = lmap->player->y + sin(rotation_angle - PI / 2)
			* lmap->player->move_speed;
	}
	else if (side_movement == -1)
	{
		*new_x = lmap->player->x + cos(rotation_angle + PI / 2)
			* lmap->player->move_speed;
		*new_y = lmap->player->y + sin(rotation_angle + PI / 2)
			* lmap->player->move_speed;
	}
	else
	{
		*new_x = lmap->player->x + cos(rotation_angle)
			* lmap->player->walk_direction * lmap->player->move_speed;
		*new_y = lmap->player->y + sin(rotation_angle)
			* lmap->player->walk_direction * lmap->player->move_speed;
	}
}
