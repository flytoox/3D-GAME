/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:36:08 by aait-mal          #+#    #+#             */
/*   Updated: 2023/12/12 18:08:17 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	normalize_angle(double angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
		angle = (2 * PI) + angle;
	return (angle);
}

int	wall_collision(double x, double y, t_map *lmap)
{
	int	map_index_x;
	int	map_index_y;
	int	ret;

	map_index_x = floor(x / TILE_SIZE);
	map_index_y = floor(y / TILE_SIZE);
	if (map_index_x < 0 || map_index_x >= lmap->width
		|| map_index_y < 0 || map_index_y >= lmap->height
		|| (!ft_strchr("01SNEW", lmap->map[map_index_y][map_index_x])))
		ret = 1;
	else
		ret = lmap->map[map_index_y][map_index_x] == '1';
	return (ret);
}

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	initialise_ray(t_ray *ray, double ray_angle)
{
	ray->ray_angle = normalize_angle(ray_angle);
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->distance = 0;
	ray->found_horz_wall_hit = false;
	ray->horz_wall_hit_x = 0;
	ray->horz_wall_hit_y = 0;
	ray->found_vert_wall_hit = false;
	ray->vert_wall_hit_x = 0;
	ray->vert_wall_hit_y = 0;
	ray->was_hit_vertical = false;
	ray->is_ray_facing_down = ray->ray_angle > 0 && ray->ray_angle < PI;
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	ray->is_ray_facing_right = ray->ray_angle < 0.5 * PI
		|| ray->ray_angle > 1.5 * PI;
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
}
