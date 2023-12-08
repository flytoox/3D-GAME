/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:37:27 by aait-mal          #+#    #+#             */
/*   Updated: 2023/12/08 21:33:53 by obelaizi         ###   ########.fr       */
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
	if (keycode == 257)
		map->player->move_speed *= 2;
	if (keycode == 256)
	{
		map->toogle_mouse = !map->toogle_mouse;
		if (!map->toogle_mouse)
			mlx_mouse_hide();
		else
			mlx_mouse_show();
	}
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
	if (keycode == 257)
		map->player->move_speed /= 2;
	return (0);
}

int	draw_frame(t_map *map)
{
	static int	i;

	update_player_movements(map, map->player->side_movement);
	mlx_clear_window(map->mlx->mlx_ptr, map->mlx->win_ptr);
	cast_all_rays(map, (double)WIN_WIDTH / WALL_STRIP_WIDTH, 1);
	mlx_put_image_to_window(map->mlx->mlx_ptr,
		map->mlx->win_ptr, map->animation[map->animation_index].img, 0, 0);
	if (!i)
	{
		if (map->animation_index < 5)
			map->animation_index = (map->animation_index + 1) % 5;
		else
			map->animation_index = (map->animation_index + 1) % 10;
	}
	i = (i + 1) % 7;
	return (0);
}

int mousemove(int x, int y, t_map *map)
{
	(void)y;
	double x1 = (double)WIN_WIDTH / 2;
	if (!map->toogle_mouse)
	{
		mlx_mouse_move(map->mlx->win_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		x1 = x - x1;
		map->player->rotation_angle += (x1 * 0.0009);
	}
	return (0);
}

int	mouse_click(int button, int x, int y, t_map *map)
{
	(void)x;
	(void)y;
	if (button == 1)
		map->animation_index = 5;
	return (0);
}

void	key_binding(t_mlx *mlx, t_map *map)
{
	mlx_mouse_hide();
	mlx_hook(mlx->win_ptr, 2, 0, &hook_key, map);
	mlx_hook(mlx->win_ptr, 3, 0, &release_key, map);
	mlx_hook(mlx->win_ptr, 17, 0, &myclose, map);
	mlx_hook(mlx->win_ptr, 6, 0, &mousemove, map);
	mlx_loop_hook(mlx->mlx_ptr, &draw_frame, map);
	mlx_mouse_hook(mlx->win_ptr, &mouse_click, map);
}
