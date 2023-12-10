/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:46:33 by obelaizi          #+#    #+#             */
/*   Updated: 2023/12/09 22:48:08 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_putstr_fd("Error\nWrong number of arguments\n", 2), 1);
	if (check_map(argv[1]))
		exit(1);
}
