/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:47:16 by obelaizi          #+#    #+#             */
/*   Updated: 2023/11/12 15:22:37 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./Libft/libft.h"
# include "./gnl/get_next_line.h"
# include <math.h>
# include <mlx.h>
# include <stdbool.h>

# define TILE_SIZE 48
# define PI 3.14159265359

typedef struct pair
{
	char	*first;
	char	*second;
}	t_strp;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

typedef struct s_player
{
	double	x;
	double	y;
	int		radius;
	int		turn_direction;
	int		walk_direction;
	double	rotation_angle;
	double	move_speed;
	double	rotation_speed;
}	t_player;

typedef struct s_map
{
	char			*s;
	int				width;
	int				height;
	t_player		*player;
	char			**map;
	t_mlx			*mlx;
	struct s_map	*next;
}	t_map;

typedef struct s_draw_params
{
	t_mlx	*mlx;
	int		x;
	int		y;
	int		width;
	int		height;
	int		color;
	int		radius;
}	t_draw_params;

char	**cust_split(char *str);

bool	good_element(char **tmp, t_strp mp[7]);
int		check_map(char *map);
void	set_my_map(t_strp mp[6]);
bool	start_map(char *line);
char	**lst_tochar(t_lst *map);
void	print_map(char **map);
char	**copy_map(char **map);
void	draw_filled_rectangle(t_draw_params *params);
void	draw_filled_circle(t_draw_params *params);
int		myclose(t_map *map);
int		hook_key(int keycode, t_map *map);
void	key_binding(t_mlx *mlx, t_map *map);
void	display_map_on_screen(char **map, t_map *lmap);
void	init_player(t_player *player);
void	init_mlx_window(t_mlx *mlx, t_map *lmap);
void	draw_map_cell(char cell, t_draw_params *params, t_player *player);
void	update_map(t_mlx *mlx, t_map *lmap);

#endif
