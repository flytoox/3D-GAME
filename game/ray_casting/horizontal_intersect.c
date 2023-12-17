/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:31:47 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/19 15:40:51 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	initialize_horz_ray_params(t_ray *ray,
	t_map *map, t_ray_params *params)
{
	params->yintercept = floor(map->player->y / TILE_SIZE) * TILE_SIZE;
	if (ray->is_ray_facing_down)
		params->yintercept += TILE_SIZE;
	params->xintercept = map->player->x
		+ (params->yintercept - map->player->y) / tan(ray->ray_angle);
	params->ystep = TILE_SIZE;
	if (ray->is_ray_facing_up)
		params->ystep *= -1;
	params->xstep = TILE_SIZE / tan(ray->ray_angle);
	if ((ray->is_ray_facing_left && params->xstep > 0)
		|| (ray->is_ray_facing_right && params->xstep < 0))
	{
		params->xstep *= -1;
	}
	ray->next_horz_touch_x = params->xintercept;
	ray->next_horz_touch_y = params->yintercept;
}

static int	horz_loop_condition(t_ray *ray, t_map *map, t_ray_params *params)
{
	params->tmp_touch = ray->next_horz_touch_y;
	if (ray->is_ray_facing_up)
		params->tmp_touch--;
	return (ray->next_horz_touch_x >= 0 && ray->next_horz_touch_x <= map->width
		&& params->tmp_touch >= 0 && params->tmp_touch <= map->height);
}

void	check_horizontal_intersect(t_ray *ray, t_map *map)
{
	t_ray_params	params;

	initialize_horz_ray_params(ray, map, &params);
	while (horz_loop_condition(ray, map, &params))
	{
		if (wall_collision(ray->next_horz_touch_x, params.tmp_touch, map))
		{
			ray->found_horz_wall_hit = true;
			ray->horz_wall_hit_x = ray->next_horz_touch_x;
			ray->horz_wall_hit_y = ray->next_horz_touch_y;
			break ;
		}
		else
		{
			ray->next_horz_touch_x += params.xstep;
			ray->next_horz_touch_y += params.ystep;
		}
	}
}
