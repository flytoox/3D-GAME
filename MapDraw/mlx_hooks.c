/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:36:20 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/17 15:50:25 by aait-mal         ###   ########.fr       */
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
	int				side_movement;
	t_draw_params	params;

	side_movement = 0;
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
		side_movement = 1;
	if (keycode == 2)
		side_movement = -1;
	params.mlx = map->mlx;
	update_map(map->mlx, map);
	update_player(params, map, side_movement);
	reinit_player(map->player);
	return (0);
}
