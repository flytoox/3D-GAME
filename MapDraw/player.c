/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:33:58 by aait-mal          #+#    #+#             */
/*   Updated: 2023/11/14 10:38:58 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player(t_player *player)
{
	player->radius = 3;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = PI / 2;
	player->move_speed = 15.0;
	player->rotation_speed = 15 * (PI / 180);
}

void	reinit_player(t_player *player)
{
	player->walk_direction = 0;
	player->turn_direction = 0;
}
