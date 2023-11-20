/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:34:52 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/20 14:54:07 by aait-mal         ###   ########.fr       */
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

void	draw_map_cell(char cell, t_draw_params *params,
	t_map *lmap)
{
	params->width = TILE_SIZE;
	params->height = TILE_SIZE;
	if (cell == '1')
	{
		params->color = 0x00FFFF;
		draw_filled_rectangle(params);
	}
	else if (cell == '0' || cell == 'N'
		|| cell == 'S' || cell == 'E' || cell == 'W')
	{
		params->color = 0x00FFFFFF;
		draw_filled_rectangle(params);
	}
	params->x = lmap->player->x;
	params->y = lmap->player->y;
	params->color = 0x00FF0000;
	params->radius = lmap->player->radius;
	draw_filled_circle(params);
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
				mlx_pixel_put(params->mlx->mlx_ptr,
					params->mlx->win_ptr, i, j, params->color);
			j++;
		}
		i++;
	}
}

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
