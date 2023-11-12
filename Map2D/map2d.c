/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:19:33 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/12 17:08:11 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_filled_rectangle(t_draw_params *params)
{
	int	i;
	int	j;

	i = 0;
	while (i < params->height)
	{
		j = 0;
		while (j < params->width)
		{
			if (i == 0 || i == params->height - 1
				|| j == 0 || j == params->width - 1)
				mlx_pixel_put(params->mlx->mlx_ptr, params->mlx->win_ptr,
					params->x + j, params->y + i, 0xA9A9A9);
			else
				mlx_pixel_put(params->mlx->mlx_ptr, params->mlx->win_ptr,
					params->x + j, params->y + i, params->color);
			j++;
		}
		i++;
	}
}

void	draw_filled_circle(t_draw_params *params)
{
	int	i;
	int	j;

	i = params->x - params->radius;
	while (i <= params->x + params->radius)
	{
		j = params->y - params->radius;
		while (j <= params->y + params->radius)
		{
			if ((i - params->x) * (i - params->x) + (j - params->y)
				* (j - params->y) <= params->radius * params->radius)
			{
				mlx_pixel_put(params->mlx->mlx_ptr,
					params->mlx->win_ptr, i, j, params->color);
			}
			j++;
		}
		i++;
	}
}

void reinit_player(t_player *player)
{
	player->walk_direction = 0;
	player->turn_direction = 0;
}

int	hook_key(int keycode, t_map *map)
{
	if (keycode == 53)
		myclose(map);
	if (keycode == 13 || keycode == 126)
	{
		map->player->walk_direction = 1;
		update_map(map->mlx, map);
		map->player->walk_direction = 0;
		printf("up\n");
	}
	if (keycode == 1 || keycode == 125)
	{
		map->player->walk_direction = -1;
		update_map(map->mlx, map);
		map->player->walk_direction = 0;
		printf("down\n");
	}
	if (keycode == 0 || keycode == 123)
	{
		if (map->player->turn_direction == 1)
			map->player->turn_direction = 0;
		else if (map->player->turn_direction == 0)
			map->player->turn_direction = -1;
		printf("left\n");
	}
	if (keycode == 2 || keycode == 124)
	{
		if (map->player->turn_direction == -1)
			map->player->turn_direction = 0;
		else if (map->player->turn_direction == 0)
			map->player->turn_direction = 1;
		printf("right\n");
	}
	return (0);
}

void	display_map_on_screen(char **map, t_map *lmap)
{
	t_mlx			mlx;
	t_player		player;
	t_draw_params	params;
	int				i;
	int				j;

	init_mlx_window(&mlx, lmap);
	init_player(&player);
	params.mlx = &mlx;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			params.x = j * TILE_SIZE;
			params.y = i * TILE_SIZE;
			draw_map_cell(map[i][j], &params, &player);
			j++;
		}
		i++;
	}
	lmap->player = &player;
	lmap->mlx = &mlx;
	lmap->map = map;
	key_binding(&mlx, lmap);
	mlx_loop(mlx.mlx_ptr);
}
