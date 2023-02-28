/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:44:31 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/28 12:21:12 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/gcube.h"

int	key_filter(int keycode, t_game *game)
{
	int	i;

	i = 0;
	debug_log(game, keycode);
	if (keycode == 53)
		end_game(game);
	else if (keycode == 13)
		move_up_down(game, 1.0);
	else if (keycode == 1)
		move_up_down(game, -1.0);
	else if (keycode == 123)
		move_cam(game, -1.0, ROTSPEED);
	else if (keycode == 124)
		move_cam(game, 1.0, ROTSPEED);
	else if (keycode == 0)
		move_left_right(game, -1.0);
	else if (keycode == 2)
		move_left_right(game, 1.0);
	else if (keycode == 49)
		open_door(game);
	game->sorted = sort_objects(game);
	return (0);
}

int	mouse_filter(int x, int y, t_game *game)
{
	if (x < WINDOW_W / 2)
		move_cam(game, -1.0, MOUSESPEED);
	else
		move_cam(game, 1.0, MOUSESPEED);
	return (0);
}
