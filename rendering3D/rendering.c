/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:52:46 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/20 00:17:24 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_mlx_window_3d(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
		WIN_WIDTH, WIN_HEIGHT, "CUB3D");
}

void	update_player_movements(t_map *lmap, int side_movement)
{
	double	new_x;
	double	new_y;

	lmap->player->rotation_angle += lmap->player->turn_direction
		* lmap->player->rotation_speed;
	set_coordinates(&new_x, &new_y, lmap, side_movement);
	if (!is_there_wall_at(new_x, new_y, lmap))
	{
		lmap->player->x = new_x;
		lmap->player->y = new_y;
	}
}

int	hook_key_3d(int keycode, t_map *map)
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
	mlx_clear_window(map->mlx->mlx_ptr, map->mlx->win_ptr);
	update_player_movements(map, side_movement);
	cast_all_rays(map, 0);
	display_2map_on_screen(map);
	cast_all_rays(map, 1);
	reinit_player(map->player);
	return (0);
}

void	key_binding_3d(t_mlx *mlx, t_map *map)
{
	mlx_hook(mlx->win_ptr, 2, 0, &hook_key_3d, map);
	mlx_hook(mlx->win_ptr, 17, 0, &myclose, map);
}

void	set_player_position(t_map *lmap)
{
	int	i;
	int	j;

	i = -1;
	while (lmap->map[++i])
	{
		j = -1;
		while (lmap->map[i][++j])
		{
			if (lmap->map[i][j] == 'N' || lmap->map[i][j] == 'S'
				|| lmap->map[i][j] == 'E' || lmap->map[i][j] == 'W')
			{
				lmap->player->x = j * TILE_SIZE + TILE_SIZE / 2;
				lmap->player->y = i * TILE_SIZE + TILE_SIZE / 2;
				return ;
			}
		}
	}
}

void	display_2map_on_screen(t_map *lmap)
{
	int				i;
	int				j;
	t_draw_params	params;

	i = -1;
	params.mlx = lmap->mlx;
	while (lmap->map[++i])
	{
		j = -1;
		while (lmap->map[i][++j])
		{
			params.x = j * TILE_SIZE;
			params.y = i * TILE_SIZE;
			draw_map_cell(lmap->map[i][j], &params, lmap);
		}
	}
	cast_all_rays(lmap, 1);
}

void	display_3d_map(char **map, t_map *lmap)
{
	t_mlx			mlx;
	t_player		player;
	t_draw_params	params;

	init_mlx_window_3d(&mlx);
	init_player(&player, map);
	params.mlx = &mlx;
	lmap->player = &player;
	lmap->mlx = &mlx;
	lmap->map = map;
	set_player_position(lmap);
	cast_all_rays(lmap, 0);
	display_2map_on_screen(lmap);
	key_binding_3d(&mlx, lmap);
	mlx_loop(mlx.mlx_ptr);
}
