/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:37:27 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/22 16:03:09 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_mlx_window(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "CUB3D");
}

int	hook_key(int keycode, t_map *map)
{
	if (keycode == 53)
		myclose(map);
	if (keycode == 13)
		map->player->walk_direction = 1;
	if (keycode == 1)
		map->player->walk_direction = -1;
	if (keycode == 123)
		map->player->turn_direction = -1;
	if (keycode == 124)
		map->player->turn_direction = 1;
	if (keycode == 0)
		map->player->side_movement = 1;
	if (keycode == 2)
		map->player->side_movement = -1;
	return (0);
}

int	release_key(int keycode, t_map *map)
{
	if (keycode == 13 || keycode == 1)
		map->player->walk_direction = 0;
	if (keycode == 123 || keycode == 124)
		map->player->turn_direction = 0;
	if (keycode == 0 || keycode == 2)
		map->player->side_movement = 0;
	return (0);
}

int	draw_frame(t_map *map)
{
	update_player_movements(map, map->player->side_movement, &map->ray);
	mlx_clear_window(map->mlx->mlx_ptr, map->mlx->win_ptr);
	cast_all_rays(map, WIN_WIDTH / WALL_STRIP_WIDTH, 1);
	return (0);
}

void	key_binding(t_mlx *mlx, t_map *map)
{
	mlx_hook(mlx->win_ptr, 2, 0, &hook_key, map);
	mlx_hook(mlx->win_ptr, 3, 0, &release_key, map);
	mlx_hook(mlx->win_ptr, 17, 0, &myclose, map);
	mlx_loop_hook(mlx->mlx_ptr, &draw_frame, map);
}
