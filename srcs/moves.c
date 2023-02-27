/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:52:05 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/27 12:52:21 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/gcube.h"

void	move_cam(t_game *game, double dir, double speed)
{
	double	o_dirx;
	double	o_cam_dirx;
	double	rot_dir;

	rot_dir = speed * dir;
	o_dirx = game->player->dir[0];
	game->player->dir[0] = o_dirx * cos(rot_dir)
		- game->player->dir[1] * sin(rot_dir);
	game->player->dir[1] = o_dirx * sin(rot_dir)
		+ game->player->dir[1] * cos(rot_dir);
	o_cam_dirx = game->player->cam_plane[0];
	game->player->cam_plane[0] = o_cam_dirx * cos(rot_dir)
		- game->player->cam_plane[1] * sin(rot_dir);
	game->player->cam_plane[1] = o_cam_dirx * sin(rot_dir)
		+ game->player->cam_plane[1] * cos(rot_dir);
}

/*
	The worst thing I have ever coded but ""KINDA"" works, so Dan is happy
*/
void	move_up_down(t_game *game, double dir)
{
	double	npos_x;
	double	npos_y;
	double	pos_x;
	double	pos_y;

	pos_x = game->player->pos[0];
	pos_y = game->player->pos[1];
	npos_x = pos_x + (game->player->dir[0] * MOVSPEED * dir);
	npos_y = pos_y + (game->player->dir[1] * MOVSPEED * dir);
	if (game->map[(int) npos_y][(int) npos_x] == '1')
		return ;
	if (game->map[(int) npos_y][(int) npos_x] == 'D')
		return ;
	if ((((int) fabs(pos_x - npos_x)) == ((int) fabs(pos_y - npos_y)))
		&& (((int) pos_x) != ((int) npos_x) && ((int) pos_y) != ((int) npos_x)))
	{
		if (dir > 0)
		{
			if (game->map[((int) pos_y) + 1][((int) pos_x)] == '1' &&
				game->map[((int) pos_y)][((int) pos_x) + 1] == '1')
				return ;
		}
		else
		{
			if (game->map[((int) pos_y) - 1][((int) pos_x)] == '1' &&
				game->map[((int) pos_y)][((int) pos_x) - 1] == '1')
				return ;
		}
	}
	game->player->pos[0] = npos_x;
	game->player->pos[1] = npos_y;
}

void	move_left_right(t_game *game, double dir)
{
	double	npos_x;
	double	npos_y;

	npos_x = game->player->pos[0]
		+ (game->player->cam_plane[0] * MOVSPEED * dir);
	npos_y = game->player->pos[1]
		+ (game->player->cam_plane[1] * MOVSPEED * dir);
	if (game->map[(int) npos_y][(int) npos_x] == '1')
		return ;
	if (game->map[(int) npos_y][(int) npos_x] == 'D')
		return ;
	game->player->pos[0] = npos_x;
	game->player->pos[1] = npos_y;
}

void	open_door(t_game *game)
{
	int	x;
	int	y;

	x = (int) game->player->pos[0];
	y = (int) game->player->pos[1];
	if (game->map[(y) + 1][x] == 'D')
		game->map[(y) + 1][x] = 'd';
	else if (game->map[(y) - 1][x] == 'D')
		game->map[(y) - 1][x] = 'd';
	else if (game->map[(y)][(x) + 1] == 'D')
		game->map[(y)][(x) + 1] = 'd';
	else if (game->map[(y)][(x) - 1] == 'D')
		game->map[(y)][(x) - 1] = 'd';
	else if (game->map[(y) + 1][x] == 'd')
		game->map[(y) + 1][x] = 'D';
	else if (game->map[(y) - 1][x] == 'd')
		game->map[(y) - 1][x] = 'D';
	else if (game->map[(y)][(x) + 1] == 'd')
		game->map[(y)][(x) + 1] = 'D';
	else if (game->map[(y)][(x) - 1] == 'd')
		game->map[(y)][(x) - 1] = 'D';
}
