/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:47:16 by obelaizi          #+#    #+#             */
/*   Updated: 2023/12/17 15:30:18 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include <math.h>
# include "../mlx/mlx.h"
# include <stdbool.h>
# include <limits.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define TILE_SIZE 64
# define PI 3.14159265359
# define FOV 60
# define MINI_MAP_SCALE_FACTOR 0.2
# define WALL_STRIP_WIDTH 1
# define MIN_DISTANCE_FROM_WALL 20
# define ERR ft_putstr_fd

typedef struct colors
{
	int		flr[3];
	int		ceilng[3];
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_colors;

typedef struct pair
{
	char	*first;
	char	*second;
}	t_strp;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
}	t_mlx;

typedef struct s_player
{
	double	x;
	double	y;
	int		radius;
	int		turn_direction;
	int		walk_direction;
	int		side_movement;
	double	rotation_angle;
	double	move_speed;
	double	rotation_speed;
}	t_player;

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
	int		ray_index;
	double	wall_strip_height;
	double	wall_top_pixel;
}	t_ray;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_data;

typedef struct s_map
{
	char			*s;
	int				width;
	int				height;
	t_player		*player;
	char			**map;
	t_mlx			*mlx;
	int				side_movement;
	double			fov_angle;
	t_data			*texture;
	int				animation_index;
	t_data			animation[10];
	t_colors		clrs;
	bool			toogle_mouse;
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

typedef struct s_ray_params
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	double	tmp_touch;
}	t_ray_params;

typedef struct s_draw_line
{
	int		dx;
	int		dy;
	float	x_increment;
	float	y_increment;
}	t_draw_line;

char	**cust_split(char *str);

bool	good_element(char **tmp, t_strp mp[7]);
int		check_file_extension(char *map);
int		open_map_file(char *map);
int		check_map_last(t_strp mp[6]);
int		check_map(char *map);
void	set_my_map(t_strp mp[6]);
bool	start_map(char *line);
char	**lst_tochar(t_lst *map);
char	**copy_map(char **map);
int		get_length(char **map);
int		get_map_height(char **map);
int		there_is_player(char **map);
bool	check_closed(char **map, int n);
bool	is_itclosed(char **map, int n, int x, int y);

void	fill_colors(int arr[], char **s);
bool	unkown_char(char **mp);

void	draw_filled_circle(t_draw_params *params, t_data *img);
void	draw_line(t_draw_params *params, int end_x, int end_y, t_data *img);

void	init_player(t_player *player, char **map);
int		is_there_wall_at(double x, double y, t_map *lmap);
void	set_coordinates(double *new_x, double *new_y,
			t_map *lmap, int side_movement);
int		wall_collision(double x, double y, t_map *lmap);
void	update_player_movements(t_map *lmap, int side_movement);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		myclose(t_map *map);
int		hook_key(int keycode, t_map *map);
void	key_binding(t_mlx *mlx, t_map *map);
void	init_mlx_window(t_mlx *mlx);

void	cast_all_rays(t_map *map, double num_rays, int is_2d);
void	cast_ray(t_ray *ray, t_map *map);
void	initialise_ray(t_ray *ray, double ray_angle);
double	normalize_angle(double angle);
double	distance_between_points(double x1, double y1, double x2, double y2);
void	check_horizontal_intersect(t_ray *ray, t_map *map);
void	check_vertical_intersect(t_ray *ray, t_map *map);
void	init_ray_data(double *fov_angle,
			double *ray_angle, t_data *img, t_map *map);
void	draw_ceiling_and_floor(t_map *lmap, t_data *img);

void	display_3d_map(char **map, t_map *lmap);
void	display_2d_map_on_screen(t_map *lmap, t_data *img);
void	render_ray_3d(t_ray *ray, t_map *map, t_data *img, t_data *texture);
int		is_collision_on_line(double x1, double y1, t_map *lmap, int steps);
void	keep_player_far_from_wall(double *check_x, double *check_y,
			t_map *lmap);

int		create_rgb(int red, int green, int blue, int alpha);
int		get_pixel_color(t_data *data, int x, int y);

void	open_textures(t_map *map, t_data *texture);
void	print_texture_from_image(t_ray *ray, t_data *img, t_data *texture);
void	render_texture(t_ray *ray, t_map *map, t_data *img);
void	destroy_textures(void *mlx, t_data *texture, int sz);

void	draw_player_minimap(t_map *lmap, t_data *img);
void	set_player_initial_position(t_map *lmap);

int		mouse_click(int button, int x, int y, t_map *map);
int		mousemove(int x, int y, t_map *map);

void	generate_map(void);
#endif
