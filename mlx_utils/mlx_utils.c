/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:37:27 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/21 23:28:10 by aait-mal         ###   ########.fr       */
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
	if (keycode == 13)
		map->player->walk_direction = 1;
	if (keycode == 1)
		map->player->walk_direction = -1;
	if (keycode == 123)
		map->player->turn_direction = -1;
	if (keycode == 124)
		map->player->turn_direction = 1;
	if (keycode == 0)
		side_movement = 1;
	if (keycode == 2)
		side_movement = -1;
	update_player_movements(map, side_movement);
	mlx_clear_window(map->mlx->mlx_ptr, map->mlx->win_ptr);
	cast_all_rays(map, 1);
	return (0);
}

int	release_key(int keycode, t_map *map)
{
	if (keycode == 13 || keycode == 1)
		map->player->walk_direction = 0;
	if (keycode == 123 || keycode == 124)
		map->player->turn_direction = 0;
	if (keycode == 0 || keycode == 2)
		map->side_movement = 0;
	return (0);
}

void	key_binding(t_mlx *mlx, t_map *map)
{
	mlx_hook(mlx->win_ptr, 2, 0, &hook_key, map);
	mlx_hook(mlx->win_ptr, 3, 0, &release_key, map);
	mlx_hook(mlx->win_ptr, 17, 0, &myclose, map);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
