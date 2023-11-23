/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:34:52 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/23 15:45:50 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_filled_rectangle(t_draw_params *params, t_data *img)
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
				my_mlx_pixel_put(img, params->x + j,
					params->y + i, 0x00A9A9A9);
			else
				my_mlx_pixel_put(img, params->x + j,
					params->y + i, params->color);
			j++;
		}
		i++;
	}
}

void	draw_map_cell(char cell, t_draw_params *params,
	t_map *lmap, t_data *img)
{
	params->width = TILE_SIZE * MINI_MAP_SCALE_FACTOR;
	params->height = TILE_SIZE * MINI_MAP_SCALE_FACTOR;
	if (cell == '1')
	{
		params->color = 0x00000000;
		draw_filled_rectangle(params, img);
	}
	else if (cell == '0' || cell == 'N'
		|| cell == 'S' || cell == 'E' || cell == 'W')
	{
		params->color = 0x00FFFFFF;
		draw_filled_rectangle(params, img);
	}
	params->x = lmap->player->x * MINI_MAP_SCALE_FACTOR;
	params->y = lmap->player->y * MINI_MAP_SCALE_FACTOR;
	params->color = 0x000000FF;
	params->radius = lmap->player->radius * MINI_MAP_SCALE_FACTOR;
	draw_filled_circle(params, img);
}

void	draw_filled_circle(t_draw_params *params, t_data *img)
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
				my_mlx_pixel_put(img, i, j, params->color);
			j++;
		}
		i++;
	}
}
