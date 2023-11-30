/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:44:57 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/30 15:45:02 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		*check_x += 12;
	else if (*check_x < lmap->player->x)
		*check_x -= 12;
	if (*check_y > lmap->player->y)
		*check_y += 12;
	else if (*check_y < lmap->player->y)
		*check_y -= 12;
}
