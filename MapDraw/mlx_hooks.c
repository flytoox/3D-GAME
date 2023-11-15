/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:36:20 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/15 23:19:38 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	key_binding(t_mlx *mlx, t_map *map)
{
	mlx_hook(mlx->win_ptr, 2, 0, &hook_key, map);
	mlx_hook(mlx->win_ptr, 17, 0, &myclose, map);
}

int	hook_key(int keycode, t_map *map)
{
	double	newX;
	double	newY;
	
	if (keycode == 53)
		myclose(map);
	if (keycode == 13 || keycode == 126)
		map->player->walk_direction += 1;
	if (keycode == 1 || keycode == 125)
		map->player->walk_direction -= 1;
	if (keycode == 123)
		map->player->turn_direction -= 1;
	if (keycode == 124)
		map->player->turn_direction += 1;
	if (keycode == 0)
	{
		/*move the player to the letf based on the his rotation angle*/
		newX = map->player->x + cos(map->player->rotation_angle - PI / 2) * map->player->move_speed;
		newY = map->player->y + sin(map->player->rotation_angle - PI / 2) * map->player->move_speed;
		if(!is_there_wall_at(newX, newY, map))
		{
			map->player->x = newX;
			map->player->y = newY;
		}
	}
	if (keycode == 2)
	{
		/*move the player to the right based on the his rotation angle*/
		newX = map->player->x + cos(map->player->rotation_angle + PI / 2) * map->player->move_speed;
		newY = map->player->y + sin(map->player->rotation_angle + PI / 2) * map->player->move_speed;
		if(!is_there_wall_at(newX, newY, map))
		{
			map->player->x = newX;
			map->player->y = newY;
		}
	}
	update_map(map->mlx, map);
	reinit_player(map->player);
	return (0);
}
