/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:13:59 by dridolfo          #+#    #+#             */
/*   Updated: 2022/10/05 19:05:04 by gcucino          ###   ########.fr       */
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
				player->posx = j;
				player->posy = i;
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
	player->angle = 45;
	player->fov = FOV;
	player->half_fov = FOV/2;
	game->player = player;
}

void	_init(t_game *game)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WINDOW_W, WINDOW_H, "GcubeDanDanDan");
	game->minimap[0] = WINDOW_W / 5;
	game->minimap[1] = WINDOW_H / 5;
	game->map = map_init("map2.gcube");
}

int	check_cond(t_game *game, int x, int y)
{
	if (game->map[(int) game->player->posy + y][(int) game->player->posx + x] == '1')
		return (1);
	//if (game->map[(int) (game->player->posx + (x * fabs(game->player->dirx) * MOVSPEED))][(int) (game->player->posy + (y * fabs(game->player->diry) * MOVSPEED))] == '1')
	//	return (1);
	return (0);
}

void	move(t_game *game, int dir)
{
	game->player->posx += ((cosf(deg_2_rad(game->player->angle)) * MOVSPEED) * dir);
	game->player->posx += ((sinf(deg_2_rad(game->player->angle)) * MOVSPEED) * dir);
}

int	key_filter(int keycode, t_game *game)
{
	int	i;

	i = 0;
	printf(YELLOW "[DEBUG]-----------------------------------\n" BLANK "posx: %lf\nposy: %lf\nangle: %lf\n",
		game->player->posx, game->player->posy, game->player->angle);
	print_mat(game->map);
	if (keycode == 53)
		end_game(game, 0);
	// else if (keycode == 13)
	// {
	// 	if (!check_cond(game, -1, 0))
	// 		move(game, -1, 0);
	// }
	// else if (keycode == 0)
	// {
	// 	if (!check_cond(game, 0, -1))
	// 		move(game, 0, -1);
	// }
	// else if (keycode == 1)
	// {
	// 	if (!check_cond(game, 1, 0))
	// 		move(game, 1, 0);
	// }
	// else if (keycode == 2)
	// {
	// 	if (!check_cond(game, 0, 1))
	// 		move(game, 0, 1);
	// }
	// else if (keycode == 123)
	// 	move_cam(game, 1);
	// else if (keycode == 124)
	// 	move_cam(game, 0);
	return (0);
}

int	game_loop(t_game *game)
{
	t_img	img;
	t_ray	ray;

	img.img = mlx_new_image(game->mlx, WINDOW_W, WINDOW_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	ft_memset(&ray, 0, sizeof(t_ray));
	raycast(game, &img, &ray);
	mlx_put_image_to_window(game->mlx, game->mlx_win, img.img, 0, 0);
	return (0);
}

int main(void)
{
	t_game	game;
	t_player	player;

	_init(&game);
	_init_directions(&game, &player);
	mlx_hook(game.mlx_win, 17, 0, end_game, &game);
	mlx_hook(game.mlx_win, 2, 1L<<0, key_filter, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
