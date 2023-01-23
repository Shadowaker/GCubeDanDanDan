/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:39:40 by gcucino           #+#    #+#             */
/*   Updated: 2023/01/23 18:37:05 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

void	draw_square_border(t_img *img, int	len, int offset_x, int offset_y)
{
	int	x;
	int	y;

	x = 0;
	while (x < len)
	{
		y = 0;
		while (y < len)
		{
			if (x == 0 || y == 0 || x == len - 1 || y == len - 1)
				my_mlx_pixel_put(img, x + offset_x, y + offset_y, 0x0000000);
			else
				my_mlx_pixel_put(img, x + offset_x, y + offset_y, 0x000089AD);
			y++;
		}
		x++;
	}
}

void	draw_square(t_img *img, int	len, int offset_x, int offset_y)
{
	int	x;
	int	y;

	x = 0;
	while (x < len)
	{
		y = 0;
		while (y < len)
		{
			my_mlx_pixel_put(img, x + offset_x, y + offset_y, 0x00ffcf56);
			y++;
		}
		x++;
	}
}

void	tdraw_circle(t_game *game, int r, int offset_x, int offset_y)
{

	int	x;
	int	y;
	int	isin;

	x = game->player->pos[0] - r;
	while (x <= (r * 2))
	{
		y = game->player->pos[1] - r;
		while (y <= (r * 2))
		{
			isin = isincircle(game->player->pos[0], game->player->pos[1], x, y);
			if (isin == 1)
				my_mlx_pixel_put(game->img, x + offset_x, y + offset_y, 0x000089AD);
			else if (isin == 2)
				my_mlx_pixel_put(game->img, x + offset_x, y + offset_y, 0x0000000);
			y++;
		}
		x++;
	}
}

void	draw_circle(t_game *game, int cx, int cy, int r)
{
	int	x;
	int	y;
	int	isin;

	y = cy - r;
	while (y <= cy + (r * 2))
	{
		x = cx - r;
		while (x <= cx + (r * 2))
		{
			isin = isincircle(cx, cy, x, y);
			if (isin == 1)
				my_mlx_pixel_put(game->img, x, y, 0xFF0089AD);
			else if (isin == 2)
				my_mlx_pixel_put(game->img, x, y, 0x0000000);
			x++;
		}
		y++;
	}
}

static void	draw_minimap(t_game *game, int start_x, int x)
{
	int	start_y;
	int	y;
	int	pix_x;
	int	pix_y;

	start_y = (int) floor(game->player->pos[1]);
	y = start_y - PLAYER_R;
	pix_x = 50 + ((x - start_x) * 10);
	while (y <= start_y + 4)
	{
		pix_y = 50 + ((start_y - y) * 10);
		if (x < 0 || y < 0 || y >= game->map_h
			|| x >= game->map_w)
			draw_square(game->img, 10, pix_x + 60, pix_y);
		else if (x == start_x && y == start_y)
			draw_circle(game, pix_x + 60, pix_y, 4);
		else if (game->map[y][x] == '1')
			draw_square_border(game->img, 10, pix_x + 60, pix_y);
		else if (game->map[y][x] != '1')
			draw_square(game->img, 10, pix_x + 60, pix_y);
		y++;
	}
}

void	render_minimap(t_game *game)
{
	int	start_x;
	int	x;

	start_x = (int) floor(game->player->pos[0]);
	x = start_x - PLAYER_R;
	while (x <= start_x + PLAYER_R)
	{
		draw_minimap(game, start_x, x);
		x++;
	}
}
