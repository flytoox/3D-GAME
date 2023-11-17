/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:00:14 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/17 21:48:21 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_ray(t_ray *ray, t_map *map)
{
	t_draw_params	params;

	params.mlx = map->mlx;
	params.x = map->player->x;
	params.y = map->player->y;
	params.color = 0x00FF0000;
	draw_line(&params, ray->wall_hit_x, ray->wall_hit_y);
}

double	normalize_angle(double angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
		angle = (2 * PI) + angle;
	return (angle);
}

void	check_horizontal_intersect(t_ray *ray, t_map *map)
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;

	yintercept = floor(map->player->y / TILE_SIZE) * TILE_SIZE;
	if (ray->is_ray_facing_down)
		yintercept += TILE_SIZE;
	xintercept = map->player->x + (yintercept - map->player->y) / tan(ray->ray_angle);
	ystep = TILE_SIZE;
	if (ray->is_ray_facing_up)
		ystep *= -1;
	xstep = TILE_SIZE / tan(ray->ray_angle);
	if (ray->is_ray_facing_left && xstep > 0)
		xstep *= -1;
	if (ray->is_ray_facing_right && xstep < 0)
		xstep *= -1;
	ray->next_horz_touch_x = xintercept;
	ray->next_horz_touch_y = yintercept;
	if (ray->is_ray_facing_up)
		ray->next_horz_touch_y--;
	
	while (ray->next_horz_touch_x >= 0 && ray->next_horz_touch_x <= map->width
		&& ray->next_horz_touch_y >= 0 && ray->next_horz_touch_y <= map->height)
	{
		if (wall_collision(ray->next_horz_touch_x, ray->next_horz_touch_y, map))
		{
			ray->found_horz_wall_hit = true;
			ray->horz_wall_hit_x = ray->next_horz_touch_x;
			ray->horz_wall_hit_y = ray->next_horz_touch_y;
			break ;
		}
		else
		{
			ray->next_horz_touch_x += xstep;
			ray->next_horz_touch_y += ystep;
		}
		
	}
}

void	check_vertical_intersect(t_ray *ray, t_map *map)
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;

	xintercept = floor(map->player->x / TILE_SIZE) * TILE_SIZE;
	if (ray->is_ray_facing_right)
		xintercept += TILE_SIZE;
	yintercept = map->player->y + (xintercept - map->player->x) * tan(ray->ray_angle);
	xstep = TILE_SIZE;
	if (ray->is_ray_facing_left)
		xstep *= -1;
	ystep = TILE_SIZE * tan(ray->ray_angle);
	if (ray->is_ray_facing_up && ystep > 0)
		ystep *= -1;
	if (ray->is_ray_facing_down && ystep < 0)
		ystep *= -1;
	ray->next_vert_touch_x = xintercept;
	ray->next_vert_touch_y = yintercept;
	if (ray->is_ray_facing_left)
		ray->next_vert_touch_x--;
	
	while (ray->next_vert_touch_x >= 0 && ray->next_vert_touch_x <= map->width
		&& ray->next_vert_touch_y >= 0 && ray->next_vert_touch_y <= map->height)
	{
		if (wall_collision(ray->next_vert_touch_x, ray->next_vert_touch_y, map))
		{
			ray->found_vert_wall_hit = true;
			ray->vert_wall_hit_x = ray->next_vert_touch_x;
			ray->vert_wall_hit_y = ray->next_vert_touch_y;
			break ;
		}
		else
		{
			ray->next_vert_touch_x += xstep;
			ray->next_vert_touch_y += ystep;
		}
	}
}

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	cast_ray(t_ray *ray, t_map *map)
{
	check_vertical_intersect(ray, map);
	check_horizontal_intersect(ray, map);
	if (ray->found_horz_wall_hit)
		ray->horz_hit_distance = distance_between_points(map->player->x, map->player->y,
			ray->horz_wall_hit_x, ray->horz_wall_hit_y);
	else
		ray->horz_hit_distance = INT_MAX;
	if (ray->found_vert_wall_hit)
		ray->vert_hit_distance = distance_between_points(map->player->x, map->player->y,
			ray->vert_wall_hit_x, ray->vert_wall_hit_y);
	else
		ray->vert_hit_distance = INT_MAX;
	
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
	printf("wall hit x: %f, wall hit y: %f\n", ray->wall_hit_x, ray->wall_hit_y);
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
	ray->is_ray_facing_right = ray->ray_angle < 0.5 * PI || ray->ray_angle > 1.5 * PI;
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
}

void	cast_all_rays(t_map *map)
{
	int		i;
	t_ray	ray;
	double	num_rays;
	double	ray_angle;

	i = -1;
	num_rays = map->width / WALL_STRIP_WIDTH;
	ray_angle = map->player->rotation_angle - (FOV_ANGLE / 2);
	while (++i < num_rays)
	{
		initialise_ray(&ray, ray_angle);
		cast_ray(&ray, map);
		render_ray(&ray, map);
		ray_angle += FOV_ANGLE / (num_rays);
	}
}
