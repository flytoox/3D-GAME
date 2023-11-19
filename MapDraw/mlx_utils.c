/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:37:27 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/19 18:27:02 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	myclose(t_map *map)
{
	map = 0;
	exit(0);
	return (0);
}

void	init_mlx_window(t_mlx *mlx, t_map *lmap)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			lmap->width, lmap->height, "CUB3D");
}
