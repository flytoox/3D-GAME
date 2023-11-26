/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:00:14 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/26 22:27:07 by aait-mal         ###   ########.fr       */
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

void	render_ray_3d(t_ray *ray, t_map *map, double fov_angle, t_data *img, t_data *texture)
{
	t_draw_params	params;
	double			ray_distance;
	double			distance_projection_plane;
	double			wall_strip_height;

	ray_distance = ray->distance
		* cos(ray->ray_angle - map->player->rotation_angle);
	distance_projection_plane = (WIN_WIDTH / 2) / tan(fov_angle / 2);
	wall_strip_height = (TILE_SIZE / ray_distance) * distance_projection_plane;
	params.mlx = map->mlx;
	params.x = ray->ray_index * WALL_STRIP_WIDTH;
	params.y = (WIN_HEIGHT / 2) - (wall_strip_height / 2);
	params.width = WALL_STRIP_WIDTH;
	params.height = wall_strip_height;
	params.color = create_rgb(255, 0, 0, 0);
	ray->wall_strip_height = wall_strip_height;
	ray->wall_top_pixel = params.y;
	print_texture_from_image(ray, img, texture);
	// draw_line(&params, params.x + params.width - 1,
	// 	params.y + params.height, img);
}

void	open_textures(t_map *map, t_data *texture)
{
	texture[0].img = mlx_xpm_file_to_image(map->mlx, "./textures/wall.xpm",
			&texture[0].width, &texture[0].height);
	texture[0].addr = mlx_get_data_addr(texture[0].img, &texture[0].bits_per_pixel,
			&texture[0].line_length, &texture[0].endian);
	texture[1].img = mlx_xpm_file_to_image(map->mlx, "./textures/wall2.xpm",
			&texture[1].width, &texture[1].height);
	texture[1].addr = mlx_get_data_addr(texture[1].img, &texture[1].bits_per_pixel,
			&texture[1].line_length, &texture[1].endian);
	texture[2].img = mlx_xpm_file_to_image(map->mlx, "./textures/wall3.xpm",
			&texture[2].width, &texture[2].height);
	texture[2].addr = mlx_get_data_addr(texture[2].img, &texture[2].bits_per_pixel,
			&texture[2].line_length, &texture[2].endian);
	texture[3].img = mlx_xpm_file_to_image(map->mlx, "./textures/wall4.xpm",
			&texture[3].width, &texture[3].height);
	texture[3].addr = mlx_get_data_addr(texture[3].img, &texture[3].bits_per_pixel,
			&texture[3].line_length, &texture[3].endian);
}

void	destroy_textures(void *mlx, t_data *texture)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(mlx, texture[i].img);
}

void	cast_all_rays(t_map *map, double num_rays, int is_2d)
{
	int		i;
	t_ray	ray;
	double	ray_angle;
	double	fov_angle;
	t_data	img;

	i = -1;
	init_ray_data(&fov_angle, &ray_angle, &img, map);
	draw_ceiling_and_floor(map, &img);
	while (++i < num_rays)
	{
		initialise_ray(&ray, ray_angle);
		cast_ray(&ray, map);
		ray.ray_index = i;
		/*check if wall is on north or sounth or west or east to draw correspanding texture*/
		if (ray.was_hit_vertical && ray.is_ray_facing_left)
			render_ray_3d(&ray, map, fov_angle, &img, &map->texture[1]);
		else if (ray.was_hit_vertical && ray.is_ray_facing_right)
			render_ray_3d(&ray, map, fov_angle, &img, &map->texture[1]);
		else if (!ray.was_hit_vertical && ray.is_ray_facing_up)
			render_ray_3d(&ray, map, fov_angle, &img, &map->texture[2]);
		else if (!ray.was_hit_vertical && ray.is_ray_facing_down)
			render_ray_3d(&ray, map, fov_angle, &img, &map->texture[2]);
		ray_angle += fov_angle / (num_rays);
	}
	if (is_2d)
		cast_2d_rays(map, &ray, &img);
	mlx_put_image_to_window(map->mlx->mlx_ptr, map->mlx->win_ptr,
		img.img, 0, 0);
	mlx_destroy_image(map->mlx->mlx_ptr, img.img);
}
