/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:21:02 by aait-mal          #+#    #+#             */
/*   Updated: 2023/12/12 18:11:34 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_line_data(t_draw_line *line,
	t_draw_params *params, int end_x, int end_y)
{
	int	steps;

	line->dx = end_x - params->x;
	line->dy = end_y - params->y;
	if (abs(line->dx) > abs(line->dy))
		steps = abs(line->dx);
	else
		steps = abs(line->dy);
	line->x_increment = line->dx / (float)steps;
	line->y_increment = line->dy / (float)steps;
}

void	draw_line(t_draw_params *params, int end_x, int end_y, t_data *img)
{
	t_draw_line	line;
	int			i;

	set_line_data(&line, params, end_x, end_y);
	i = 0;
	while (i <= abs(line.dx) || i <= abs(line.dy))
	{
		if (params->x >= 0 && params->x < WIN_WIDTH && params->y >= 0
			&& params->y < WIN_HEIGHT)
			my_mlx_pixel_put(img, params->x, params->y, params->color);
		params->x += round(line.x_increment);
		params->y += round(line.y_increment);
		i++;
	}
}
