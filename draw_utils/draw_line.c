/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:21:02 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/22 15:48:56 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_line(t_draw_params *params, int end_x, int end_y, t_data *img)
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
		if (params->x >= 0 && params->x < WIN_WIDTH
			&& params->y >= 0 && params->y < WIN_HEIGHT)
			my_mlx_pixel_put(img, params->x, params->y, params->color);
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
