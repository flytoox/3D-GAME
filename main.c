/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:46:33 by obelaizi          #+#    #+#             */
/*   Updated: 2023/12/04 21:04:28 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_putstr_fd("Error\nWrong number of arguments\n", 2), 1);
	if (check_map(argv[1]))
		exit(1);
}
