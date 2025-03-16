/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:44:31 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/28 15:07:33 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/gcube.h"

int	key_filter(int keycode, t_game *game)
{
	int	i;

	i = 0;
	if (keycode == ESCAPE)
		end_game(game);
	else if (keycode == UP)
		move_up_down(game, 1.0);
	else if (keycode == DOWN)
		move_up_down(game, -1.0);
	else if (keycode == ARROW_LEFT)
		move_cam(game, -1.0, ROTSPEED);
	else if (keycode == ARROW_RIGHT)
		move_cam(game, 1.0, ROTSPEED);
	else if (keycode == LEFT)
		move_left_right(game, -1.0);
	else if (keycode == RIGHT)
		move_left_right(game, 1.0);
	else if (keycode == SPACE)
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
