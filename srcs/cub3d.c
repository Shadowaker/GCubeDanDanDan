/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:13:59 by dridolfo          #+#    #+#             */
/*   Updated: 2022/10/11 12:43:04 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/gcube.h"


void	culo()
{
	static int ass = 0;

	printf("Culo %d\n", ass);
	ass++;
}

int end_game(t_game *game, int arg)
{
	if (game && arg)
		;
	free_mat(game->map);
	exit(0);
}

int	_init_culo(t_game *game, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N')
			{
				player->posx = j + 0.5;
				player->posy = i + 0.5;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	_init_directions(t_game *game, t_player *player)
{
	if (_init_culo(game, player) == 0)
		return ;
	player->angle = 90;
	player->fov = FOV;
	player->half_fov = FOV/2;
	game->player = player;
}

void	_init(t_game *game, t_img *img)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WINDOW_W, WINDOW_H, "GcubeDanDanDan");
	game->minimap[0] = 150;
	game->minimap[1] = 150;
	game->map = map_init("map2.gcube");
	img->img = mlx_new_image(game->mlx, WINDOW_W, WINDOW_H);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	game->img = img;
}

void	move_cam(t_game *game, double dir)
{
	game->player->angle += (ROTSPEED * dir);
}

void	move_up_down(t_game *game, double dir)
{
	double newx;
	double newy;

	newx = game->player->posx + ((cosf(deg_2_rad(game->player->angle)) * MOVSPEED) * dir);
	newy = game->player->posy + ((sinf(deg_2_rad(game->player->angle)) * MOVSPEED) * dir);
	if (game->map[(int) newy][(int) newx] != '1')
	{
		game->player->posx = newx;
		game->player->posy = newy;
	}
}

int	key_filter(int keycode, t_game *game)
{
	int	i;

	i = 0;
	printf(YELLOW "[DEBUG]-----------------------------------\n" BLANK "posx: %lf\nposy: %lf\nangle: %lf\nkeycode: %d\n",
		game->player->posx, game->player->posy, game->player->angle, keycode);
	// print_mat(game->map);
	if (keycode == 53)
		end_game(game, 0);
	else if (keycode == 13)
	{
		move_up_down(game, 1.0);
	}
	//else if (keycode == 0)
	//{
	//	if (!check_cond(game, 0, -1))
	//		move(game, 0, -1);
	//}
	else if (keycode == 1)
	{
		move_up_down(game, -1.0);
	}
	//else if (keycode == 2)
	//{
	//	if (!check_cond(game, 0, 1))
	//		move(game, 0, 1);
	//}
	else if (keycode == 123)
		move_cam(game, -1);
	else if (keycode == 124)
		move_cam(game, 1);
	return (0);
}

int	game_loop(t_game *game)
{
	t_ray	ray;

	ft_memset(&ray, 0, sizeof(t_ray));
	draw_minimap(game, game->img);
	raycast(game, game->img, &ray);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img->img, 0, 0);
	return (0);
}

int main(void)
{
	t_game		game;
	t_player	player;
	t_img		img;

	_init(&game, &img);
	_init_directions(&game, &player);
	mlx_hook(game.mlx_win, 17, 0, end_game, &game);
	mlx_hook(game.mlx_win, 2, 1L<<0, key_filter, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
