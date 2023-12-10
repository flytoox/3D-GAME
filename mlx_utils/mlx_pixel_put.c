/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:51:41 by aait-mal          #+#    #+#             */
/*   Updated: 2023/12/10 13:23:47 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	myclose(t_map *map)
{
	map = 0;
	exit(0);
	return (0);
}

int	mousemove(int x, int y, t_map *map)
{
	double	x1;

	x1 = (double)WIN_WIDTH / 2;
	(void)y;
	if (!map->toogle_mouse)
	{
		mlx_mouse_move(map->mlx->win_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		x1 = x - x1;
		map->player->rotation_angle += (x1 * 0.0009);
	}
	return (0);
}

int	mouse_click(int button, int x, int y, t_map *map)
{
	(void)x;
	(void)y;
	if (button == 1)
		map->animation_index = 5;
	return (0);
}
