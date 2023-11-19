/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_projection_3d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:49:01 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/19 16:07:48 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_3d_projection(t_map *lmap, t_draw_params	*params)
{
	int				i;
	int				j;

	// Project the walls
	i = -1;
	while (lmap->map[++i])
	{
		j = -1;
		while (lmap->map[i][++j])
		{
			params->x = j * TILE_SIZE;
			params->y = i * TILE_SIZE;
			draw_map_cell(lmap->map[i][j], params, lmap, 1);
		}
	}
	cast_all_rays(lmap);
}

void	update_3d_projection(t_map *lmap, t_draw_params params)
{
	render_3d_projection(lmap, &params);
}
