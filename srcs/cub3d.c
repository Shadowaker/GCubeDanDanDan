/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:13:59 by dridolfo          #+#    #+#             */
/*   Updated: 2022/11/21 15:13:26 by dridolfo         ###   ########.fr       */
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
				player->pos[0] = j + 0.5;
				player->pos[1] = i + 0.5;
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
	player->dir[0] = -1.0;
	player->dir[1] = 0.0;
	player->cam_plane[0] = 0.0;
	player->cam_plane[1] = -0.66;
	game->player = player;
}

void	_init(t_game *game, t_img *img, t_textures *texts)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WINDOW_W, WINDOW_H, "GcubeDanDanDan");
	game->minimap[0] = 150;
	game->minimap[1] = 150;
	game->map = map_init("map3");
	game->map_h = 10;
	game->map_w = 10;
	img->img = mlx_new_image(game->mlx, WINDOW_W, WINDOW_H);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	game->img = img;
	game->texts = texts;
}

void	move_cam(t_game *game, double dir)
{
	double	o_dirx;
	double	o_cam_dirx;
	double	rot_dir;

	rot_dir = ROTSPEED * dir;
	o_dirx = game->player->dir[0];
	game->player->dir[0] = o_dirx * cos(rot_dir) - game->player->dir[1] * sin(rot_dir);
	game->player->dir[1] = o_dirx * sin(rot_dir) + game->player->dir[1] * cos(rot_dir);
	o_cam_dirx = game->player->cam_plane[0];
	game->player->cam_plane[0] = o_cam_dirx * cos(rot_dir) - game->player->cam_plane[1] * sin(rot_dir);
	game->player->cam_plane[1] = o_cam_dirx * sin(rot_dir) + game->player->cam_plane[1] * cos(rot_dir);
}

void	move_up_down(t_game *game, double dir)
{
	double	npos_x;
	double	npos_y;

	npos_x = game->player->pos[0] + (game->player->dir[0] * MOVSPEED * dir);
	npos_y = game->player->pos[1] + (game->player->dir[1] * MOVSPEED * dir);

	if (game->map[(int) npos_y][(int) npos_x] == '1')
		return ;
	game->player->pos[0] = npos_x;
	game->player->pos[1] = npos_y;
}

int	key_filter(int keycode, t_game *game)
{
	int	i;

	i = 0;
	printf(YELLOW "[DEBUG]-----------------------------------\n" BLANK "posx: %lf\nposy: %lf\ncam x: %lf\ncam y: %lf\nkeycode: %d\n",
		game->player->pos[0], game->player->pos[1], game->player->cam_plane[0], game->player->cam_plane[1], keycode);
	if (keycode == 53)
		end_game(game, 0);
	else if (keycode == 13)
	{
		move_up_down(game, 1.0);
	}
	else if (keycode == 1)
	{
		move_up_down(game, -1.0);
	}
	else if (keycode == 123)
		move_cam(game, -1.0);
	else if (keycode == 124)
		move_cam(game, 1.0);
	return (0);
}

int	game_loop(t_game *game)
{
	t_ray	ray;

	ft_memset(&ray, 0, sizeof(t_ray));
	engine(game, game->img, &ray);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img->img, 0, 0);
	return (0);
}

int main(void)
{
	t_game		game;
	t_player	player;
	t_img		img;
	t_textures	texts;

	_init(&game, &img, &texts);
	_init_directions(&game, &player);
	printf(YELLOW "[DEBUG]-----------------------------------\n" BLANK "posx: %lf\nposy: %lf\ncam x: %lf\ncam y: %lf\nkeycode: %d\n",
		game.player->pos[0], game.player->pos[1], game.player->cam_plane[0], game.player->cam_plane[1], 0);
	mlx_hook(game.mlx_win, 17, 0, end_game, &game);
	mlx_hook(game.mlx_win, 2, 1L<<0, key_filter, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
