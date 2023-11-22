/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:00:14 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/22 13:20:36 by aait-mal         ###   ########.fr       */
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

void	render_ray_3d(t_ray *ray, t_map *map, double fov_angle, t_data *img)
{
	t_draw_params	params;
	double			ray_distance;
	double			distance_projection_plane;
	double			wall_strip_height;

	ray_distance = ray->distance * cos(ray->ray_angle - map->player->rotation_angle);
	distance_projection_plane = (WIN_WIDTH / 2) / tan(fov_angle / 2);
	wall_strip_height = (TILE_SIZE / ray_distance) * distance_projection_plane;
	params.mlx = map->mlx;
	params.x = ray->ray_index * WALL_STRIP_WIDTH;
	params.y = (WIN_HEIGHT / 2) - (wall_strip_height / 2);
	params.width = WALL_STRIP_WIDTH;
	params.height = wall_strip_height;
	params.color = 0x00FF0000;
	draw_line(&params, params.x + params.width - 1, params.y + params.height, img);
}

void	draw_ceiling_and_floor(t_map *lmap, t_data *img)
{
	int				i;
	t_draw_params	params;

	i = -1;
	params.mlx = lmap->mlx;
	while (++i < WIN_WIDTH)
	{
		params.x = i;
		params.y = 0;
		params.height = WIN_HEIGHT / 2;
		params.color = 0x0000FFFF;
		draw_line(&params, params.x + 0, params.y + params.height, img);
		params.y = WIN_HEIGHT / 2;
		params.color = 0x00A9A9A9;
		draw_line(&params, params.x + 0, params.y + params.height, img);
	}
}

void	cast_all_rays(t_map *map, int is_2d)
{
	int		i;
	t_ray	ray;
	double	num_rays;
	double	ray_angle;
	double	fov_angle;
	t_data	img;

	i = -1;
	num_rays = WIN_WIDTH / WALL_STRIP_WIDTH;
	fov_angle = FOV * (PI / 180);
	ray_angle = map->player->rotation_angle - (fov_angle / 2);
	img.img = mlx_new_image(map->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	draw_ceiling_and_floor(map, &img);
	while (++i < num_rays)
	{
		initialise_ray(&ray, ray_angle);
		cast_ray(&ray, map);
		ray.ray_index = i;
		render_ray_3d(&ray, map, fov_angle, &img);
		map->ray = ray;
		ray_angle += fov_angle / (num_rays);
	}
	if (is_2d)
	{
		i = -1;
		num_rays = WIN_WIDTH / WALL_STRIP_WIDTH;
		fov_angle = FOV * (PI / 180);
		ray_angle = map->player->rotation_angle - (fov_angle / 2);
		display_2d_map_on_screen(map, &img);
		while (++i < num_rays)
		{
			initialise_ray(&ray, ray_angle);
			cast_ray(&ray, map);
			ray.ray_index = i;
			render_ray(&ray, map, &img);
			ray_angle += fov_angle / (num_rays);
		}
	}
	mlx_put_image_to_window(map->mlx->mlx_ptr, map->mlx->win_ptr,
		img.img, 0, 0);
	mlx_destroy_image(map->mlx->mlx_ptr, img.img);
}
