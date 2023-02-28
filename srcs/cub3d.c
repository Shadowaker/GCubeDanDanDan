/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:13:59 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/28 10:36:22 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/gcube.h"

void	culo(int *i)
{
	static int	ass = 0;

	if (!i)
	{
		printf("Culo %d\n", ass);
		ass++;
	}
	else
		printf("Culo %d\n", *i);
}

void	debug_log(t_game *game, int keycode)
{
	printf(YELLOW "[DEBUG] -----------------------------------\n" BLANK
		"posx: %lf\nposy: %lf\ncam x: %lf\ncam y: %lf\nkeycode: %d\n",
		game->player->pos[0], game->player->pos[1],
		game->player->cam_plane[0], game->player->cam_plane[1], keycode);
}

int	end_game(t_game *game, int arg)
{
	if (game && arg)
		;
	free_mat(game->map);
	clear_objs(&game->objs);
	exit(0);
}

int	game_loop(t_game *game)
{
	t_ray		ray;
	static int	lock = 0;

	if (lock == 170)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		engine(game, game->img, &ray);
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->img->img, 0, 0);
		update_animation(game);
		lock = 0;
	}
	else
		lock++;
	return (0);
}

int	main(int argc, char **argv)
{
	t_game			game;
	t_player		player;
	t_img			img;
	t_textures		texts;
	t_animations	ani;

	if (argc != 2)
		return (printf(RED "ERROR:\t" BLANK "Bad argument.\nNo map passed.\n"));
	_init_game(&game, &img, &texts, argv[1]);
	_init_texture(&game, &texts, &ani);
	_init_directions(&game, &player);
	debug_log(&game, 0);
	mlx_hook(game.mlx_win, 17, 0, end_game, &game);
	mlx_hook(game.mlx_win, 2, 1L << 0, key_filter, &game);
	mlx_hook(game.mlx_win, 6, 0, mouse_filter, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
