/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:13:59 by dridolfo          #+#    #+#             */
/*   Updated: 2022/10/02 17:31:55 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/gcube.h"

int ass = 0;

void	culo()
{
	printf("Culo %d\n", ass);
	ass++;
}

int end_game(t_game *game, int arg)
{
	if (game && arg)
		;
	exit(0);
}

void	_init_directions(t_game *game, t_state *state)
{
	state->posx = 22;
	state->posy = 22;
	state->dirx = 0;
	state->diry = -1;
	state->angle[0] = 0.66;
	state->angle[1] = 0;
	game->state = state;
}

void	_init(t_game *game)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WINDOW_W, WINDOW_H, "GcubeDanDanDan");
	game->map = map_init("map.gcube");
}

int	check_cond(t_game *game, int x, int y)
{
	if (game->map[(int) game->state->posy + y][(int) game->state->posx + x] == '1')
			return (1);
	return (0);
}

void	move(t_game *game, int x, int y)
{
	game->state->posx += (((double) x) * MOVSPEED);
	game->state->posy += (((double) y) * MOVSPEED);
}

void	move_cam(t_game *game, int i)
{
	double	old_dirx;
	double	old_angle;

	old_dirx = game->state->dirx;
	old_angle = game->state->angle[0];
	if (i)
	{
		game->state->dirx = game->state->dirx * cos(ROTSPEED) - game->state->diry * sin(ROTSPEED);
		game->state->diry = old_dirx * sin(ROTSPEED) + game->state->diry * cos(ROTSPEED);
		game->state->angle[0] = game->state->angle[0] * cos(ROTSPEED) - game->state->angle[1] * sin(ROTSPEED);
		game->state->angle[1] = old_angle * sin(ROTSPEED) + game->state->angle[1] * cos(ROTSPEED);
	}
	else
	{
		game->state->dirx = game->state->dirx * cos(-ROTSPEED) - game->state->diry * sin(-ROTSPEED);
		game->state->diry = old_dirx * sin(-ROTSPEED) + game->state->diry * cos(-ROTSPEED);
		game->state->angle[0] = game->state->angle[0] * cos(-ROTSPEED) - game->state->angle[1] * sin(-ROTSPEED);
		game->state->angle[1] = old_angle * sin(-ROTSPEED) + game->state->angle[1] * cos(-ROTSPEED);
	}
}

int	key_filter(int keycode, t_game *game)
{
	int	i;

	i = 0;
	printf(YELLOW "[DEBUG]-----------------------------------\n" BLANK "posx: %lf\nposy: %lf\ndirx: %lf\ndiry: %lf\nanglex: %lf\nangley: %lf\ncamx: %lf\n",
		game->state->posx, game->state->posy, game->state->dirx, game->state->diry, game->state->angle[0], game->state->angle[1],
		game->state->camx);
	if (keycode == 53)
		end_game(game, 0);
	else if (keycode == 13)
	{
		if (!check_cond(game, -1, 0))
			move(game, -1, 0);
	}
	else if (keycode == 0)
	{
		if (!check_cond(game, 0, -1))
			move(game, 0, -1);
	}
	else if (keycode == 1)
	{
		if (!check_cond(game, 1, 0))
			move(game, 1, 0);
	}
	else if (keycode == 2)
	{
		if (!check_cond(game, 0, 1))
			move(game, 0, 1);
	}
	else if (keycode == 123)
		move_cam(game, 1);
	else if (keycode == 124)
		move_cam(game, 0);
	return (0);
}

int	game_loop(t_game *game)
{
	raycast(game);
	return (0);
}

int main(void)
{
	t_game	game;
	t_state	state;

	_init(&game);
	_init_directions(&game, &state);
	mlx_hook(game.mlx_win, 17, 0, end_game, &game);
	mlx_hook(game.mlx_win, 2, 1L<<0, key_filter, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
