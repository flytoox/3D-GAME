/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:10:58 by aait-mal          #+#    #+#             */
/*   Updated: 2023/12/10 16:02:13 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray_data(double *fov_angle,
	double *ray_angle, t_data *img, t_map *map)
{
	*fov_angle = FOV * (PI / 180);
	*ray_angle = map->player->rotation_angle - (*fov_angle / 2);
	img->img = mlx_new_image(map->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

int	create_rgb(int red, int green, int blue, int alpha)
{
	return (alpha << 24 | red << 16 | green << 8 | blue);
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
		params.color = create_rgb(lmap->clrs.ceilng[0], lmap->clrs.ceilng[1],
				lmap->clrs.ceilng[2], 0);
		draw_line(&params, params.x + 0, params.y + params.height, img);
		params.y = WIN_HEIGHT / 2;
		params.color = create_rgb(lmap->clrs.flr[0], lmap->clrs.flr[1],
				lmap->clrs.flr[2], 0);
		draw_line(&params, params.x + 0, params.y + params.height, img);
	}
}
