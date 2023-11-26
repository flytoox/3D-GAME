/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:44:35 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/26 15:30:43 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_pixel_color(t_data *data, int x, int y)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}


void	print_texture_from_image(t_ray *ray, t_data *img, t_data *texture)
{
	/*calculate texture_offset_x*/
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
		texture_offset_y = (y - ray->wall_top_pixel) * ((double)texture->height / ray->wall_strip_height);
		texture_color = get_pixel_color(texture, texture_offset_x, texture_offset_y);
		my_mlx_pixel_put(img, ray->ray_index, y, texture_color);
		y++;
	}
}
