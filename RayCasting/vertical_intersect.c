/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:32:24 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/18 20:49:55 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	initialize_vert_ray_params(t_ray *ray,
	t_map *map, t_ray_params *params)
{
	params->xintercept = floor(map->player->x / TILE_SIZE) * TILE_SIZE;
	if (ray->is_ray_facing_right)
		params->xintercept += TILE_SIZE;
	params->yintercept = map->player->y
		+ (params->xintercept - map->player->x) * tan(ray->ray_angle);
	params->xstep = TILE_SIZE;
	if (ray->is_ray_facing_left)
		params->xstep *= -1;
	params->ystep = TILE_SIZE * tan(ray->ray_angle);
	if ((ray->is_ray_facing_up && params->ystep > 0)
		|| (ray->is_ray_facing_down && params->ystep < 0))
	{
		params->ystep *= -1;
	}
	ray->next_vert_touch_x = params->xintercept;
	ray->next_vert_touch_y = params->yintercept;
}

static int	vert_loop_condition(t_ray *ray, t_map *map, t_ray_params *params)
{
	params->tmp_touch = ray->next_vert_touch_x;
	if (ray->is_ray_facing_left)
		params->tmp_touch--;
	return (ray->next_vert_touch_x >= 0 && ray->next_vert_touch_x <= map->width
		&& ray->next_vert_touch_y >= 0
		&& ray->next_vert_touch_y <= map->height);
}

void	check_vertical_intersect(t_ray *ray, t_map *map)
{
	t_ray_params	params;

	initialize_vert_ray_params(ray, map, &params);
	while (vert_loop_condition(ray, map, &params))
	{
		if (wall_collision(params.tmp_touch, ray->next_vert_touch_y, map))
		{
			ray->found_vert_wall_hit = true;
			ray->vert_wall_hit_x = ray->next_vert_touch_x;
			ray->vert_wall_hit_y = ray->next_vert_touch_y;
			break ;
		}
		else
		{
			ray->next_vert_touch_x += params.xstep;
			ray->next_vert_touch_y += params.ystep;
		}
	}
}
