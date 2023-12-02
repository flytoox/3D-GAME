/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:44:35 by aait-mal          #+#    #+#             */
/*   Updated: 2023/12/02 22:50:22 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_pixel_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	print_texture_from_image(t_ray *ray, t_data *img, t_data *texture)
{
	int	texture_offset_x;
	int	texture_offset_y;
	int	texture_color;
	int	y;

	if (ray->was_hit_vertical)
		texture_offset_x = (int)ray->wall_hit_y % TILE_SIZE;
	else
		texture_offset_x = (int)ray->wall_hit_x % TILE_SIZE;
	y = ray->wall_top_pixel;
	while (y < ray->wall_strip_height + ray->wall_top_pixel)
	{
		texture_offset_y = (y - ray->wall_top_pixel)
			* ((double)texture->height / ray->wall_strip_height);
		texture_color = get_pixel_color(texture,
				texture_offset_x, texture_offset_y);
		my_mlx_pixel_put(img, ray->ray_index, y, texture_color);
		y++;
	}
}

void	open_textures(t_map *map, t_data *texture)
{
	texture[0].img = mlx_xpm_file_to_image(map->mlx, map->clrs.ea,
			&texture[0].width, &texture[0].height);
	texture[1].img = mlx_xpm_file_to_image(map->mlx, map->clrs.we,
			&texture[1].width, &texture[1].height);
	texture[2].img = mlx_xpm_file_to_image(map->mlx, map->clrs.no,
			&texture[2].width, &texture[2].height);
	texture[3].img = mlx_xpm_file_to_image(map->mlx, map->clrs.so,
			&texture[3].width, &texture[3].height);
	if (!texture[0].img || !texture[1].img
		|| !texture[2].img || !texture[3].img)
		return (printf("Error on opening textures\n"), exit(1));
	texture[0].addr = mlx_get_data_addr(texture[0].img,
			&texture[0].bits_per_pixel, &texture[0].line_length,
			&texture[0].endian);
	texture[1].addr = mlx_get_data_addr(texture[1].img,
			&texture[1].bits_per_pixel, &texture[1].line_length,
			&texture[1].endian);
	texture[2].addr = mlx_get_data_addr(texture[2].img,
			&texture[2].bits_per_pixel, &texture[2].line_length,
			&texture[2].endian);
	texture[3].addr = mlx_get_data_addr(texture[3].img,
			&texture[3].bits_per_pixel, &texture[3].line_length,
			&texture[3].endian);
}

void	destroy_textures(void *mlx, t_data *texture)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(mlx, texture[i].img);
}

void	render_texture(t_ray *ray, t_map *map, t_data *img)
{
	if (ray->was_hit_vertical && ray->is_ray_facing_left)
		render_ray_3d(ray, map, img, &map->texture[0]);
	else if (ray->was_hit_vertical && ray->is_ray_facing_right)
		render_ray_3d(ray, map, img, &map->texture[1]);
	else if (!ray->was_hit_vertical && ray->is_ray_facing_up)
		render_ray_3d(ray, map, img, &map->texture[2]);
	else if (!ray->was_hit_vertical && ray->is_ray_facing_down)
		render_ray_3d(ray, map, img, &map->texture[3]);
}
