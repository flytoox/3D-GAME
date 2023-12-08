/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:52:46 by aait-mal          #+#    #+#             */
/*   Updated: 2023/12/08 21:36:03 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_player_movements(t_map *lmap, int side_movement)
{
	double	new_x;
	double	new_y;
	double	check_x;
	double	check_y;

	lmap->player->rotation_angle += lmap->player->turn_direction
		* lmap->player->rotation_speed;
	set_coordinates(&new_x, &new_y, lmap, side_movement);
	check_x = new_x;
	check_y = new_y;
	keep_player_far_from_wall(&check_x, &check_y, lmap);
	if (new_x >= 0 && new_x < lmap->width * TILE_SIZE
		&& new_y >= 0 && new_y < lmap->height * TILE_SIZE)
	{
		if (!is_collision_on_line(check_x, check_y, lmap, 200))
		{
			lmap->player->x = new_x;
			lmap->player->y = new_y;
		}
	}
}

void	set_player_initial_position(t_map *lmap)
{
	int	i;
	int	j;

	i = -1;
	while (lmap->map[++i])
	{
		j = -1;
		while (lmap->map[i][++j])
		{
			if (lmap->map[i][j] == 'N' || lmap->map[i][j] == 'S'
				|| lmap->map[i][j] == 'E' || lmap->map[i][j] == 'W')
			{
				lmap->player->x = j * TILE_SIZE + (double)TILE_SIZE / 2;
				lmap->player->y = i * TILE_SIZE + (double)TILE_SIZE / 2;
				return ;
			}
		}
	}
}

void    fill_minimap(t_map *lmap)
{
    int    i;
    int    j;
    int    cnti,cntj;

    i = lmap->player->y / TILE_SIZE + 7;
    if (i >= get_map_height(lmap->map))
        i = get_map_height(lmap->map) - 1;
    i -= 14;
    if (i < 0)
        i = 0;
    cnti = 0;
    while (lmap->map[i] && cnti < 15)
    {
        j = lmap->player->x / TILE_SIZE + 7;
        if (j >= (int)ft_strlen(lmap->map[i]))
            j = ft_strlen(lmap->map[i]) - 1;
        j -= 14;
        if (j < 0)
            j = 0;
        cntj = 0;
        while (lmap->map[i][j] && cntj < 14)
        {
            // if ((lmap->map[i][j] == 'N' || lmap->map[i][j] == 'S'
            //     || lmap->map[i][j] == 'E' || lmap->map[i][j] == 'W'))
            // {
            //     lmap->minimp.Px = cntj;
            //     lmap->minimp.Py = cnti;
            // }
            lmap->minimp.mp[cnti][cntj++]= lmap->map[i][j++];
        }
        lmap->minimp.mp[cnti++][cntj] = '\0';
        i++;
    }
    lmap->minimp.height = cnti;
}

void	display_2d_map_on_screen(t_map *lmap, t_data *img)
{
	int				i;
	int				j;
	t_draw_params	params;
	
	i = -1;
	params.mlx = lmap->mlx;
	fill_minimap(lmap);
	while (lmap->minimp.mp[++i] && i < lmap->minimp.height)
	{
		j = -1;
		while (lmap->minimp.mp[i][++j])
		{
			params.x = j * TILE_SIZE * MINI_MAP_SCALE_FACTOR;
			params.y = i * TILE_SIZE * MINI_MAP_SCALE_FACTOR;
			draw_map_cell(lmap->minimp.mp[i][j], &params, lmap, img);
		}
	}
}

void	check_xpm(t_data *animation, char *pth, t_map *lmap)
{
	animation->img = mlx_xpm_file_to_image(lmap->mlx->mlx_ptr,
			pth, &animation->width, &animation->height);
	if (!animation->img)
		return (printf("Error on opening animation files\n"), exit(1));
}

void	open_animation(t_map *lmap)
{
	lmap->animation_index = 0;
	check_xpm(&lmap->animation[0],"./textures/animation/01.xpm" , lmap);
	check_xpm(&lmap->animation[1],"./textures/animation/02.xpm" , lmap);
	check_xpm(&lmap->animation[2],"./textures/animation/03.xpm" , lmap);
	check_xpm(&lmap->animation[3],"./textures/animation/04.xpm" , lmap);
	check_xpm(&lmap->animation[4],"./textures/animation/02.xpm" , lmap);
	check_xpm(&lmap->animation[5],"./textures/animation/F01.xpm" , lmap);
	check_xpm(&lmap->animation[6],"./textures/animation/F02.xpm" , lmap);
	check_xpm(&lmap->animation[7],"./textures/animation/F03.xpm" , lmap);
	check_xpm(&lmap->animation[8],"./textures/animation/F04.xpm" , lmap);
	check_xpm(&lmap->animation[9],"./textures/animation/F05.xpm" , lmap);
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
