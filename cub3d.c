/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:13:59 by dridolfo          #+#    #+#             */
/*   Updated: 2022/09/27 15:07:56 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/gcube.h"

int end_game(t_game *game, int arg)
{
	if (game && arg)
		;
	exit(0);
}

void	state_init(t_game *game)
{
	t_state	state;

	state.posx = 22;
	state.posy = 22;
	state.dirx = -1;
	state.diry = 0;
	state.camx = 0;
	game->state = &state;
}

void	_init(t_game *game)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WINDOW_W, WINDOW_H, "GcubeDanDanDan");

	//game->map = map_init();
}

int	game_loop(t_game *game)
{
	//	render();
	if (game->tmp == 0)
		raycast(game);
	game->tmp == 1;
}

int main(void)
{
	t_game	game;

	game.tmp = 0;
	_init(&game);
	// init framebuffer
	// init stato
	// caricamento mappa

	mlx_hook(game.mlx_win, 17, 0, end_game, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);

	//mlx_key_hook(game.mlx_win, key_filter, &game);

	mlx_loop(game.mlx);

}
