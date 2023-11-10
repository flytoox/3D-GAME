/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:47:16 by obelaizi          #+#    #+#             */
/*   Updated: 2023/11/10 10:35:56 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./Libft/libft.h"
# include "./gnl/get_next_line.h"
# include <math.h>
# include <mlx.h>
# include <stdbool.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct pair
{
	char	*first;
	char	*second;
}	t_strp;

typedef struct s_map
{
	char			*s;
	struct s_map	*next;
}	t_map;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

char	**cust_split(char *str);

bool	good_element(char **tmp, t_strp mp[7]);
int		check_map(char *map);
void	set_my_map(t_strp mp[6]);
bool	start_map(char *line);
char	**lst_tochar(t_lst *map);

#endif
