/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:51:57 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/12 17:05:05 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	myclose(t_map *map)
{
	map = 0;
	exit(0);
	return (0);
}

void	update_player(t_draw_params params, t_map *lmap)
{
	if (lmap->player->turn_direction == -1)
		lmap->player->x -= lmap->player->move_speed;
	else if (lmap->player->turn_direction == 1)
		lmap->player->x += lmap->player->move_speed;
	else if (lmap->player->walk_direction == 1)
		lmap->player->y -= lmap->player->move_speed;
	else if (lmap->player->walk_direction == -1)
		lmap->player->y += lmap->player->move_speed;
	printf("x: %f, y: %f\n", lmap->player->x, lmap->player->y);
	params.x = lmap->player->x;
	params.y = lmap->player->y;
	params.color = 0x00FF0000;
	params.radius = lmap->player->radius;
	draw_filled_circle(&params);
}

void	update_map(t_mlx *mlx, t_map *lmap)
{
	int				i;
	int				j;
	t_draw_params	params;
	
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	i = 0;
	params.mlx = mlx;
	while (lmap->map[i])
	{
		j = 0;
		while (lmap->map[i][j])
		{
			params.x = j * TILE_SIZE;
			params.y = i * TILE_SIZE;
			params.width = TILE_SIZE;
			params.height = TILE_SIZE;
			if (lmap->map[i][j] == '1')
			{
				params.color = 0x00FFFF;
				draw_filled_rectangle(&params);
			}
			else if (lmap->map[i][j] == '0' || lmap->map[i][j] == 'N')
			{
				params.color = 0x00FFFFFF;
				draw_filled_rectangle(&params);
			}
			j++;
		}
		i++;
	}
	update_player(params, lmap);
}

void	key_binding(t_mlx *mlx, t_map *map)
{
	mlx_hook(mlx->win_ptr, 2, 0, &hook_key, map);
	mlx_hook(mlx->win_ptr, 17, 0, &myclose, map);
}

void	init_mlx_window(t_mlx *mlx, t_map *lmap)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			lmap->width, lmap->height, "CUB3D");
}

void	draw_map_cell(char cell, t_draw_params *params, t_player *player)
{
	params->width = TILE_SIZE;
	params->height = TILE_SIZE;
	if (cell == '1')
	{
		params->color = 0x00FFFF;
		draw_filled_rectangle(params);
	}
	else if (cell == '0' || cell == 'N')
	{
		params->color = 0x00FFFFFF;
		draw_filled_rectangle(params);
	}
	if (cell == 'N')
	{
		params->x += TILE_SIZE / 2;
		params->y += TILE_SIZE / 2;
		player->x = params->x;
		player->y = params->y;
		params->color = 0x00FF0000;
		params->radius = player->radius;
		draw_filled_circle(params);
	}
}
