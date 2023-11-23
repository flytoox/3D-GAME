/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:21:02 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/22 16:50:21 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_line_data(t_draw_line *line, t_draw_params *params,
	int end_x, int end_y)
{
	line->dx = abs(end_x - params->x);
	line->dy = abs(end_y - params->y);
	if (params->x < end_x)
		line->sx = 1;
	else
		line->sx = -1;
	if (params->y < end_y)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = (line->dx > line->dy) - (line->dy > line->dx) / 2;
	line->e2 = 0;
}

void	draw_line(t_draw_params *params, int end_x, int end_y, t_data *img)
{
	t_draw_line	line;

	set_line_data(&line, params, end_x, end_y);
	while (1)
	{
		if (params->x >= 0 && params->x < WIN_WIDTH
			&& params->y >= 0 && params->y < WIN_HEIGHT)
			my_mlx_pixel_put(img, params->x, params->y, params->color);
		if (params->x == end_x && params->y == end_y)
			break ;
		line.e2 = line.err;
		if (line.e2 > -line.dx)
		{
			line.err -= line.dy;
			params->x += line.sx;
		}
		if (line.e2 < line.dy)
		{
			line.err += line.dx;
			params->y += line.sy;
		}
	}
}
