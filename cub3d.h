/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:47:16 by obelaizi          #+#    #+#             */
/*   Updated: 2023/09/26 22:17:30 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./Libft/libft.h"
# include "./gnl/get_next_line.h"
# include <math.h>
# include <mlx.h>
# include <stdbool.h>

typedef struct pair
{
	char	*first;
	char	*second;
}t_strp;

char	**cust_split(char *str);

bool	good_element(char **tmp, t_strp mp[7]);
int		check_map(char *map);

#endif
