/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:52:46 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/30 15:45:43 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_player_movements(t_map *lmap, int side_movement)
{
	double	new_x;
	double	new_y;
	double	check_x;
	double	check_y;

	lmap->player->rotation_angle += lmap->player->turn_direction
		* lmap->player->rotation_speed;
	set_coordinates(&new_x, &new_y, lmap, side_movement);
	check_x = new_x;
	check_y = new_y;
	keep_player_far_from_wall(&check_x, &check_y, lmap);
	if (new_x >= 0 && new_x < lmap->width * TILE_SIZE
		&& new_y >= 0 && new_y < lmap->height * TILE_SIZE)
	{
		if (!is_collision_on_line(check_x, check_y, lmap, 200))
		{
			lmap->player->x = new_x;
			lmap->player->y = new_y;
		}
	}
}

void	set_player_initial_position(t_map *lmap)
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

void	display_2d_map_on_screen(t_map *lmap, t_data *img)
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
			params.x = j * TILE_SIZE * MINI_MAP_SCALE_FACTOR;
			params.y = i * TILE_SIZE * MINI_MAP_SCALE_FACTOR;
			draw_map_cell(lmap->map[i][j], &params, lmap, img);
		}
	}
}

void	display_3d_map(char **map, t_map *lmap)
{
	t_mlx			mlx;
	t_player		player;
	t_draw_params	params;
	t_data			texture[4];

	init_mlx_window(&mlx);
	init_player(&player, map);
	params.mlx = &mlx;
	lmap->player = &player;
	lmap->mlx = &mlx;
	lmap->map = map;
	set_player_initial_position(lmap);
	open_textures(lmap, texture);
	lmap->texture = texture;
	cast_all_rays(lmap, WIN_WIDTH / WALL_STRIP_WIDTH, 1);
	key_binding(&mlx, lmap);
	mlx_loop(mlx.mlx_ptr);
	destroy_textures(lmap->mlx->mlx_ptr, lmap->texture);
}
