/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:00:14 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/19 18:26:11 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_wall_hit_distance(t_ray *ray)
{
	if (ray->horz_hit_distance < ray->vert_hit_distance)
	{
		ray->wall_hit_x = ray->horz_wall_hit_x;
		ray->wall_hit_y = ray->horz_wall_hit_y;
		ray->distance = ray->horz_hit_distance;
		ray->was_hit_vertical = false;
	}
	else
	{
		ray->wall_hit_x = ray->vert_wall_hit_x;
		ray->wall_hit_y = ray->vert_wall_hit_y;
		ray->distance = ray->vert_hit_distance;
		ray->was_hit_vertical = true;
	}
}

void	cast_ray(t_ray *ray, t_map *map)
{
	check_vertical_intersect(ray, map);
	check_horizontal_intersect(ray, map);
	if (ray->found_horz_wall_hit)
		ray->horz_hit_distance = distance_between_points(map->player->x,
				map->player->y, ray->horz_wall_hit_x, ray->horz_wall_hit_y);
	else
		ray->horz_hit_distance = INT_MAX;
	if (ray->found_vert_wall_hit)
		ray->vert_hit_distance = distance_between_points(map->player->x,
				map->player->y, ray->vert_wall_hit_x, ray->vert_wall_hit_y);
	else
		ray->vert_hit_distance = INT_MAX;
	set_wall_hit_distance(ray);
}

void	cast_all_rays(t_map *map)
{
	int		i;
	t_ray	ray;
	double	num_rays;
	double	ray_angle;
	double	fov_angle;

	i = -1;
	num_rays = map->width / WALL_STRIP_WIDTH;
	fov_angle = 60 * (PI / 180);
	ray_angle = map->player->rotation_angle - (fov_angle / 2);
	while (++i < num_rays)
	{
		initialise_ray(&ray, ray_angle);
		cast_ray(&ray, map);
		render_ray(&ray, map);
		ray_angle += fov_angle / (num_rays);
	}
}
