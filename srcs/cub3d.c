/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:13:59 by dridolfo          #+#    #+#             */
/*   Updated: 2022/10/01 19:08:46 by dridolfo         ###   ########.fr       */
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

void	_init(t_game *game)
{
	t_state state;

	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WINDOW_W, WINDOW_H, "GcubeDanDanDan");
	game->map = map_init("map.gcube");
	ft_memset(&state, 0, sizeof(t_state));
	state.posx = 12;
	state.posy = 12;
	state.dirx = -1;
	state.diry = 0;
	state.angle[0] = 0;
	state.angle[1] = 0.66;
	game->state = &state;
	//init_directions(game, 'N');
	printf("EMILY %lf %lf %lf %lf %lf %lf %lf\n", game->state->posx, game->state->posy,
	game->state->dirx, game->state->diry, game->state->angle[0], game->state->angle[1],
	game->state->camx);
}

int	check_cond(t_game *game, int x, int y)
{
	if (game->map[(int) game->state->posy + y][(int) game->state->posx + x] == '1')
			return (1);
	return (0);
}

void	move(t_game *game, int x, int y)
{
	game->state->posx += (x * 0.33);
	game->state->posy += (y * 0.33);
}

int	key_filter(int keycode, t_game *game)
{
	int	i;

	i = 0;
	printf("EMILY %lf %lf %lf %lf %lf %lf %lf\n", game->state->posx, game->state->posy,
	game->state->dirx, game->state->diry, game->state->angle[0], game->state->angle[1],
	game->state->camx);
	if (keycode == 53)
		end_game(game, 0);
	else if (keycode == 13 || keycode == 126)
	{
		if (!check_cond(game, 0, -1))
			move(game, 0, -1);
		else
			end_game(game, 0);
	}
	else if (keycode == 0 || keycode == 123)
	{
		if (!check_cond(game, -1, 0))
			move(game, -1, 0);
		else
			end_game(game, 0);
	}
	else if (keycode == 1 || keycode == 125)
	{
		if (!check_cond(game, 0, 1))
			move(game, 0, 1);
		else
			end_game(game, 0);
	}
	else if (keycode == 2 || keycode == 124)
	{
		if (!check_cond(game, 0, -1))
			move(game, 0, -1);
		else
			end_game(game, 0);
	}
	printf("CULO %lf %lf %lf %lf %lf %lf %lf\n", game->state->posx, game->state->posy,
		game->state->dirx, game->state->diry, game->state->angle[0], game->state->angle[1],
		game->state->camx);
	return (0);
}

int	game_loop(t_game *game)
{
	printf("CULO %lf %lf %lf %lf %lf %lf %lf\n", game->state->posx, game->state->posy,
		game->state->dirx, game->state->diry, game->state->angle[0], game->state->angle[1],
		game->state->camx);
	raycast(game);
	return (0);
}

int main(void)
{
	t_game	game;

	_init(&game);
	printf("EMILY %lf %lf %lf %lf %lf %lf %lf\n", game.state->posx, game.state->posy,
	game.state->dirx, game.state->diry, game.state->angle[0], game.state->angle[1],
	game.state->camx);
	mlx_hook(game.mlx_win, 17, 0, end_game, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_key_hook(game.mlx_win, key_filter, &game);
	mlx_loop(game.mlx);
}
