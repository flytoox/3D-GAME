/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:52:46 by aait-mal          #+#    #+#             */
/*   Updated: 2023/12/17 15:26:39 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	display_2d_map_on_screen(t_map *lmap, t_data *img)
{
	int	cnti;
	int	cntj;
	int	i;
	int	j;

	i = lmap->player->y - (100 * 3);
	cnti = -1;
	while (++cnti < 200)
	{
		cntj = -1;
		j = lmap->player->x - (75 * 3);
		while (++cntj < 150)
		{
			if (i < 0 || i / TILE_SIZE >= get_map_height(lmap->map) || j < 0
				|| j / TILE_SIZE >= (int)ft_strlen(lmap->map[i / TILE_SIZE])
				|| lmap->map[i / TILE_SIZE][j / TILE_SIZE] == '1')
				my_mlx_pixel_put(img, cntj, cnti, 0x000000);
			else
				my_mlx_pixel_put(img, cntj, cnti, create_rgb(192, 192, 192, 0));
			j += 3;
		}
		i += 3;
	}
	draw_player_minimap(lmap, img);
}

void	check_xpm(t_data *animation, char *pth, t_map *lmap)
{
	animation->img = mlx_xpm_file_to_image(lmap->mlx->mlx_ptr, pth,
			&animation->width, &animation->height);
	if (!animation->img)
		return (ERR("Error\nOn opening animation files\n", 2), exit(1));
}

void	open_animation(t_map *lmap)
{
	lmap->animation_index = 0;
	check_xpm(&lmap->animation[0], "./game/textures/animation/01.xpm", lmap);
	check_xpm(&lmap->animation[1], "./game/textures/animation/02.xpm", lmap);
	check_xpm(&lmap->animation[2], "./game/textures/animation/03.xpm", lmap);
	check_xpm(&lmap->animation[3], "./game/textures/animation/04.xpm", lmap);
	check_xpm(&lmap->animation[4], "./game/textures/animation/02.xpm", lmap);
	check_xpm(&lmap->animation[5], "./game/textures/animation/F01.xpm", lmap);
	check_xpm(&lmap->animation[6], "./game/textures/animation/F02.xpm", lmap);
	check_xpm(&lmap->animation[7], "./game/textures/animation/F03.xpm", lmap);
	check_xpm(&lmap->animation[8], "./game/textures/animation/F04.xpm", lmap);
	check_xpm(&lmap->animation[9], "./game/textures/animation/F05.xpm", lmap);
}

void	display_3d_map(char **map, t_map *lmap)
{
	t_mlx			mlx;
	t_player		player;
	t_draw_params	params;
	t_data			texture[4];

	init_mlx_window(&mlx);
	lmap->toogle_mouse = false;
	init_player(&player, map);
	params.mlx = &mlx;
	lmap->player = &player;
	lmap->mlx = &mlx;
	lmap->map = map;
	set_player_initial_position(lmap);
	open_animation(lmap);
	open_textures(lmap, texture);
	lmap->texture = texture;
	cast_all_rays(lmap, (double)WIN_WIDTH / WALL_STRIP_WIDTH, 1);
	key_binding(&mlx, lmap);
	mlx_loop(mlx.mlx_ptr);
	destroy_textures(lmap->mlx->mlx_ptr, lmap->texture, 4);
	destroy_textures(lmap->mlx->mlx_ptr, lmap->animation, 10);
}
