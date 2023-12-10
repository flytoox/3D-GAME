/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:44:57 by aait-mal          #+#    #+#             */
/*   Updated: 2023/12/10 12:59:11 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
				lmap->player->x = j * TILE_SIZE + (double)TILE_SIZE / 2;
				lmap->player->y = i * TILE_SIZE + (double)TILE_SIZE / 2;
				return ;
			}
		}
	}
}

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

void	draw_player_minimap(t_map *lmap, t_data *img)
{
	t_draw_params	params;

	params.x = 75;
	params.y = 100;
	params.color = create_rgb(255, 0, 0, 0);
	params.mlx = lmap->mlx;
	params.radius = lmap->player->radius * MINI_MAP_SCALE_FACTOR;
	draw_filled_circle(&params, img);
	draw_line(&params, params.x + cos(lmap->player->rotation_angle) * 4,
		params.y + sin(lmap->player->rotation_angle) * 4, img);
}

int	is_collision_on_line(double x1, double y1, t_map *lmap, int steps)
{
	double	dx;
	double	dy;
	double	check_x;
	double	check_y;
	int		i;

	dx = (x1 - lmap->player->x) / steps;
	dy = (y1 - lmap->player->y) / steps;
	i = 0;
	while (i < steps)
	{
		check_x = lmap->player->x + dx * i;
		check_y = lmap->player->y + dy * i;
		if (is_there_wall_at(check_x, check_y, lmap))
			return (1);
		if (is_there_wall_at(check_x + 2, check_y, lmap))
			return (1);
		if (is_there_wall_at(check_x - 2, check_y, lmap))
			return (1);
		i++;
	}
	return (0);
}

void	keep_player_far_from_wall(double *check_x, double *check_y,
		t_map *lmap)
{
	if (*check_x > lmap->player->x)
		*check_x += 5;
	else if (*check_x < lmap->player->x)
		*check_x -= 5;
	if (*check_y > lmap->player->y)
		*check_y += 5;
	else if (*check_y < lmap->player->y)
		*check_y -= 5;
}
