/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:37:27 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/20 15:16:30 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	myclose(t_map *map)
{
	map = 0;
	exit(0);
	return (0);
}

void	init_mlx_window(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "CUB3D");
}

int	hook_key(int keycode, t_map *map)
{
	int				side_movement;

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
	mlx_clear_window(map->mlx->mlx_ptr, map->mlx->win_ptr);
	update_player_movements(map, side_movement);
	cast_all_rays(map, 0);
	display_2d_map_on_screen(map);
	cast_all_rays(map, 1);
	reinit_player(map->player);
	return (0);
}

void	key_binding(t_mlx *mlx, t_map *map)
{
	mlx_hook(mlx->win_ptr, 2, 0, &hook_key, map);
	mlx_hook(mlx->win_ptr, 17, 0, &myclose, map);
}
