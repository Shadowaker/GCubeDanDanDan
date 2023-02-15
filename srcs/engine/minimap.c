/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:39:40 by gcucino           #+#    #+#             */
/*   Updated: 2023/02/15 12:35:24 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

static void	draw_player(t_img *img, int	len, int offset_x, int offset_y)
{
	int	x;
	int	y;

	x = 0;
	while (x < len)
	{
		y = 0;
		while (y < len)
		{
			my_mlx_pixel_put(img, x + offset_x, y + offset_y, 0x00c22620);
			y++;
		}
		x++;
	}
}

static void	draw_minimap(t_game *game, int start_x, int x)
{
	int	start_y;
	int	y;
	int	pix[2];

	start_y = (int) floor(game->player->pos[1]);
	y = start_y + PLAYER_R;
	pix[0] = 50 + ((x - start_x) * 10);
	while (y >= start_y - 4)
	{
		pix[1] = 50 - ((start_y - y) * 10);
		if (x < 0 || y < 0 || y >= game->map_h
			|| x >= game->map_w)
			draw_black_square(game->img, 10, pix[0] + 10, pix[1]);
		else if (game->map[y][x] == '1')
			draw_square_border(game->img, 10, pix[0] + 10, pix[1]);
		else if (game->map[y][x] == 'D')
			draw_green_square(game->img, 10, pix[0] + 10, pix[1]);
		else if (game->map[y][x] != '1')
			draw_square(game->img, 10, pix[0] + 10, pix[1]);
		y--;
	}
}

void	render_minimap(t_game *game)
{
	int	start_x;
	int	x;

	start_x = (int) floor(game->player->pos[0]);
	x = start_x + PLAYER_R;
	while (x >= start_x - 4)
	{
		draw_minimap(game, start_x, x);
		x--;
	}
	draw_player(game->img, 10, 60, 50);
}
