/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:19:33 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/19 16:03:14 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_line(t_draw_params *params, int end_x, int end_y)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(end_x - params->x);
	dy = abs(end_y - params->y);
	if (params->x < end_x)
		sx = 1;
	else
		sx = -1;
	if (params->y < end_y)
		sy = 1;
	else
		sy = -1;
	err = (dx > dy) - (dy > dx) / 2;
	e2 = 0;
	while (1)
	{
		mlx_pixel_put(params->mlx->mlx_ptr, params->mlx->win_ptr,
			params->x, params->y, params->color);
		if (params->x == end_x && params->y == end_y)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			params->x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			params->y += sy;
		}
	}
}

void	draw_filled_circle(t_draw_params *params, t_map *lmap)
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
				mlx_pixel_put(params->mlx->mlx_ptr,
					params->mlx->win_ptr, i, j, params->color);
			j++;
		}
		i++;
	}
	(void)lmap;
}

int	is_there_wall_at(double x, double y, t_map *lmap)
{
	int	map_index_x;
	int	map_index_y;
	int	ret;

	map_index_x = floor(x / TILE_SIZE);
	map_index_y = floor(y / TILE_SIZE);
	if (map_index_x < 0 || map_index_x >= lmap->width
		|| map_index_y < 0 || map_index_y >= lmap->height)
		ret = 1;
	else
		ret = lmap->map[map_index_y][map_index_x] == '1';
	return (ret);
}

void	set_coordinates(double *new_x, double *new_y,
	t_map *lmap, int side_movement)
{
	double	rotation_angle;

	rotation_angle = lmap->player->rotation_angle;
	if (side_movement == 1)
	{
		*new_x = lmap->player->x + cos(rotation_angle - PI / 2)
			* lmap->player->move_speed;
		*new_y = lmap->player->y + sin(rotation_angle - PI / 2)
			* lmap->player->move_speed;
	}
	else if (side_movement == -1)
	{
		*new_x = lmap->player->x + cos(rotation_angle + PI / 2)
			* lmap->player->move_speed;
		*new_y = lmap->player->y + sin(rotation_angle + PI / 2)
			* lmap->player->move_speed;
	}
	else
	{
		*new_x = lmap->player->x + cos(rotation_angle)
			* lmap->player->walk_direction * lmap->player->move_speed;
		*new_y = lmap->player->y + sin(rotation_angle)
			* lmap->player->walk_direction * lmap->player->move_speed;
	}
}

void	update_player(t_draw_params params, t_map *lmap, int side_movement)
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
	(void)params;
	// params.x = lmap->player->x;
	// params.y = lmap->player->y;
	// params.color = 0x00FF0000;
	// params.radius = lmap->player->radius;
	// draw_filled_circle(&params, lmap);
}
