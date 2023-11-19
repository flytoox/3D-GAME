/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:47:16 by obelaizi          #+#    #+#             */
/*   Updated: 2023/11/19 15:56:26 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./Libft/libft.h"
# include "./Gnl/get_next_line.h"
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <limits.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TILE_SIZE 32
# define PI 3.14159265359
# define FOV 60
# define MINI_MAP_SCALE_FACTOR 0.2
# define WALL_STRIP_WIDTH 1

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
	int				side_movement;
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

typedef struct s_ray
{
	double	ray_angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	double	horz_hit_distance;
	double	vert_hit_distance;
	double	next_horz_touch_x;
	double	next_horz_touch_y;
	double	next_vert_touch_x;
	double	next_vert_touch_y;
	double	horz_wall_hit_x;
	double	horz_wall_hit_y;
	double	vert_wall_hit_x;
	double	vert_wall_hit_y;
	int		found_horz_wall_hit;
	int		found_vert_wall_hit;
	int		was_hit_vertical;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;
	int		wall_hit_content;
}	t_ray;

typedef struct s_ray_params
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	double	tmp_touch;
}	t_ray_params;

char	**cust_split(char *str);

bool	good_element(char **tmp, t_strp mp[7]);
int		check_map(char *map);
void	set_my_map(t_strp mp[6]);
bool	start_map(char *line);
char	**lst_tochar(t_lst *map);
void	print_map(char **map);
char	**copy_map(char **map);
void	draw_filled_rectangle(t_draw_params *params);
void	draw_filled_circle(t_draw_params *params, t_map *lmap);
int		myclose(t_map *map);
int		hook_key(int keycode, t_map *map);
void	key_binding(t_mlx *mlx, t_map *map);
void	display_map_on_screen(char **map, t_map *lmap);
void	init_player(t_player *player, char **map);
void	init_mlx_window(t_mlx *mlx, t_map *lmap);
void	draw_map_cell(char cell, t_draw_params *params,
			t_map *lmap, int draw_p);
void	draw_line(t_draw_params *params, int end_x, int end_y);
void	update_map(t_mlx *mlx, t_map *lmap);
void	update_player(t_draw_params params, t_map *lmap, int side_movement);
int		is_there_wall_at(double x, double y, t_map *lmap);
int		wall_collision(double x, double y, t_map *lmap);
void	reinit_player(t_player *player);
void	cast_all_rays(t_map *map);
void	initialise_ray(t_ray *ray, double ray_angle);
void	render_ray(t_ray *ray, t_map *map);
double	normalize_angle(double angle);
int		wall_collision(double x, double y, t_map *lmap);
double	distance_between_points(double x1, double y1, double x2, double y2);
void	check_horizontal_intersect(t_ray *ray, t_map *map);
void	check_vertical_intersect(t_ray *ray, t_map *map);
void	render_3d_projection(t_map *lmap, t_draw_params	*params);
void	update_3d_projection(t_map *lmap, t_draw_params params);

#endif
