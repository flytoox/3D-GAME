/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:00:14 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/19 23:47:41 by aait-mal         ###   ########.fr       */
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

void	draw_rectangle(t_draw_params *params)
{
	int	i;
	int	j;

	i = 0;
	while (i < params->height)
	{
		j = 0;
		while (j < params->width)
		{
			mlx_pixel_put(params->mlx->mlx_ptr, params->mlx->win_ptr,
				params->x + j, params->y + i, params->color);
			j++;
		}
		i++;
	}
}

void	render_ray_3d(t_ray *ray, t_map *map, double fov_angle, int ray_index)
{
	t_draw_params	params;
	double			ray_distance;
	double			distance_projection_plane;
	double			wall_strip_height;
	
	ray_distance = ray->distance;
	distance_projection_plane = (WIN_WIDTH / 2) / tan(fov_angle / 2);
	wall_strip_height = (TILE_SIZE / ray_distance) * distance_projection_plane;

	params.mlx = map->mlx;
	params.x = ray_index * WALL_STRIP_WIDTH;
	params.y = (WIN_HEIGHT / 2) - (wall_strip_height / 2);
	params.width = WALL_STRIP_WIDTH;
	params.height = wall_strip_height;
	params.color = 0x00FF0000;
	draw_rectangle(&params);
}

void	cast_all_rays(t_map *map, int is_2d)
{
	int		i;
	t_ray	ray;
	double	num_rays;
	double	ray_angle;
	double	fov_angle;

	i = -1;
	num_rays = WIN_WIDTH / WALL_STRIP_WIDTH;
	fov_angle = 60 * (PI / 180);
	ray_angle = map->player->rotation_angle - (fov_angle / 2);
	while (++i < num_rays)
	{
		initialise_ray(&ray, ray_angle);
		cast_ray(&ray, map);
		if (is_2d)
			render_ray(&ray, map);
		else
			render_ray_3d(&ray, map, fov_angle, i);
		ray_angle += fov_angle / (num_rays);
	}
}
