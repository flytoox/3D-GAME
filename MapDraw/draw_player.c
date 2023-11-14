/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:19:33 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/14 10:40:00 by aait-mal         ###   ########.fr       */
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

void	draw_filled_circle(t_draw_params *params, t_player *player)
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
	draw_line(params, params->x + cos(player->rotation_angle)
		* 20, params->y + sin(player->rotation_angle) * 20);
}

void	update_player(t_draw_params params, t_map *lmap)
{
	lmap->player->rotation_angle += lmap->player->turn_direction
		* lmap->player->rotation_speed;
	lmap->player->x += cos(lmap->player->rotation_angle)
		* lmap->player->walk_direction * lmap->player->move_speed;
	lmap->player->y += sin(lmap->player->rotation_angle)
		* lmap->player->walk_direction * lmap->player->move_speed;
	printf("x: %f, y: %f\n", lmap->player->x, lmap->player->y);
	params.x = lmap->player->x;
	params.y = lmap->player->y;
	params.color = 0x00FF0000;
	params.radius = lmap->player->radius;
	draw_filled_circle(&params, lmap->player);
}