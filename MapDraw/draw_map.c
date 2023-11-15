/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:34:52 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/15 23:17:54 by aait-mal         ###   ########.fr       */
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

void	draw_map_cell(char cell, t_draw_params *params, t_player *player)
{
	params->width = TILE_SIZE;
	params->height = TILE_SIZE;
	if (cell == '1')
	{
		params->color = 0x00FFFF;
		draw_filled_rectangle(params);
	}
	else if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
	{
		params->color = 0x00FFFFFF;
		draw_filled_rectangle(params);
	}
	if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
	{
		params->x += TILE_SIZE / 2;
		params->y += TILE_SIZE / 2;
		player->x = params->x;
		player->y = params->y;
		params->color = 0x00FF0000;
		params->radius = player->radius;
		draw_filled_circle(params, player);
	}
}

void	display_map_on_screen(char **map, t_map *lmap)
{
	t_mlx			mlx;
	t_player		player;
	t_draw_params	params;
	int				i;
	int				j;

	init_mlx_window(&mlx, lmap);
	init_player(&player, map);
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

void	update_map(t_mlx *mlx, t_map *lmap)
{
	// int				i;
	// int				j;
	t_draw_params	params;
	
	// mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	// i = 0;
	params.mlx = mlx;
	// while (lmap->map[i])
	// {
	// 	j = 0;
	// 	while (lmap->map[i][j])
	// 	{
	// 		params.x = j * TILE_SIZE;
	// 		params.y = i * TILE_SIZE;
	// 		params.width = TILE_SIZE;
	// 		params.height = TILE_SIZE;
	// 		if (lmap->map[i][j] == '1')
	// 		{
	// 			params.color = 0x00FFFF;
	// 			draw_filled_rectangle(&params);
	// 		}
	// 		else if (lmap->map[i][j] == '0' || lmap->map[i][j] == 'N'
	// 			|| lmap->map[i][j] == 'S' || lmap->map[i][j] == 'E' || lmap->map[i][j] == 'W')
	// 		{
	// 			params.color = 0x00FFFFFF;
	// 			draw_filled_rectangle(&params);
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
	update_player(params, lmap);
}
