/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:46:47 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/27 13:01:32 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/gcube.h"

static void	set_we(t_player *player, char c)
{
	if (c == 'W')
	{
		player->dir[0] = -1.0;
		player->dir[1] = 0.0;
		player->cam_plane[0] = 0.0;
		player->cam_plane[1] = -0.66;
	}
	else
	{
		player->dir[0] = 1.0;
		player->dir[1] = 0.0;
		player->cam_plane[0] = 0.0;
		player->cam_plane[1] = 0.66;
	}
}

static void	set_player(t_player *player, char c)
{
	if (c == 'N')
	{
		player->dir[0] = 0.0;
		player->dir[1] = -1.0;
		player->cam_plane[0] = 0.66;
		player->cam_plane[1] = -0.0;
	}
	else if (c == 'S')
	{
		player->dir[0] = 0.0;
		player->dir[1] = 1.0;
		player->cam_plane[0] = -0.66;
		player->cam_plane[1] = 0.0;
	}
	else
		set_we(player, c);
}

static int	_init_player(t_game *game, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (ft_isinstr("NWSE", game->map[i][j]))
			{
				player->pos[0] = j + 0.5;
				player->pos[1] = i + 0.5;
				set_player(player, game->map[i][j]);
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
	if (_init_player(game, player) == 0)
		return ;
	game->player = player;
	get_all_objects(game);
	ft_lstprint(game->objs);
	game->sorted = sort_objects(game);
	ft_sortprint(game->objs);
}

void	_init(t_game *game, t_img *img, t_textures *texts, char *path,
			t_fireplace *fp, t_deatheater *de)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WINDOW_W, WINDOW_H, "GcubeDanDanDan");
	if (parser(game, texts, path))
	{
		printf("Error\n");
		exit(127);
	}
	if (map_validator(game->map) != 0)
	{
		printf("Error\n");
		exit(127);
	}
	game->map_h = ft_matlen(game->map);
	game->map_w = ft_strlen(game->map[0]);
	img->img = mlx_new_image(game->mlx, WINDOW_W, WINDOW_H);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
							&img->endian);
	game->img = img;
	texts->fireplaces = fp;
	texts->deatheaters = de;
	game->texts = texts;
	game->texts->wall = game->texts->no;
	game->texts->wall_side = game->texts->ea;
	game->a_phase = 0;
	load_door(game, &(game->texts->door), DOOR);
	load_sprites(game, game->texts);
}
