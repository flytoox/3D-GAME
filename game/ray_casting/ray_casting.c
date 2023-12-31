/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:00:14 by aait-mal          #+#    #+#             */
/*   Updated: 2023/12/10 16:02:03 by obelaizi         ###   ########.fr       */
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

void	draw_rectangle(t_draw_params *params, t_data *img)
{
	int		i;
	int		j;

	i = 0;
	while (i < params->height)
	{
		j = 0;
		while (j < params->width)
		{
			my_mlx_pixel_put(img, j, i, params->color);
			j++;
		}
		i++;
	}
}

void	render_ray_3d(t_ray *ray, t_map *map, t_data *img, t_data *texture)
{
	t_draw_params	params;
	double			ray_distance;
	double			distance_projection_plane;
	double			wall_strip_height;

	ray_distance = ray->distance
		* cos(ray->ray_angle - map->player->rotation_angle);
	distance_projection_plane = (double)WIN_WIDTH / 2 / tan(map->fov_angle / 2);
	wall_strip_height = (TILE_SIZE / ray_distance) * distance_projection_plane;
	params.mlx = map->mlx;
	params.x = ray->ray_index * WALL_STRIP_WIDTH;
	params.y = ((double)WIN_HEIGHT / 2) - (wall_strip_height / 2);
	params.width = WALL_STRIP_WIDTH;
	params.height = wall_strip_height;
	params.color = create_rgb(255, 0, 0, 0);
	ray->wall_strip_height = wall_strip_height;
	ray->wall_top_pixel = params.y;
	print_texture_from_image(ray, img, texture);
}

void	cast_all_rays(t_map *map, double num_rays, int is_2d)
{
	int		i;
	t_ray	ray;
	double	ray_angle;
	t_data	img;

	i = -1;
	init_ray_data(&map->fov_angle, &ray_angle, &img, map);
	draw_ceiling_and_floor(map, &img);
	while (++i < num_rays)
	{
		initialise_ray(&ray, ray_angle);
		cast_ray(&ray, map);
		ray.ray_index = i;
		render_texture(&ray, map, &img);
		ray_angle += map->fov_angle / (num_rays);
	}
	if (is_2d)
		display_2d_map_on_screen(map, &img);
	mlx_put_image_to_window(map->mlx->mlx_ptr, map->mlx->win_ptr,
		img.img, 0, 0);
	mlx_destroy_image(map->mlx->mlx_ptr, img.img);
}
