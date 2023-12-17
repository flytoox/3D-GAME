/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:46:33 by obelaizi          #+#    #+#             */
/*   Updated: 2023/12/17 15:29:51 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		generate_map();
		check_map("mapTemp.cub");
	}
	else if (argc != 2)
		return (ERR("Error\nWrong number of arguments\n", 2), 1);
	else if (check_map(argv[1]))
		exit(1);
	return (0);
}
