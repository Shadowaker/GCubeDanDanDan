/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:39:40 by gcucino           #+#    #+#             */
/*   Updated: 2022/12/08 15:57:05 by dridolfo         ###   ########.fr       */
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
/*
void	tdraw_minimap(t_game *game, t_img *img)
{
	;
	int	x;
	int	y;

	x = 0;
	draw_square(img, 200, 10, 10);
	while (game->map[x] != NULL)
	{
		y = 0;
		while (game->map[x][y] != '\0')
		{
			if (game->map[y][x] == '1')
				draw_square_border(img, 20, (x * 20) + 10,  (y * 20) + 10);
			//if (game->map[y][x] == 'N')
			//	draw_square_border(img, 8, (x * 20) + 16,  (y * 20) + 16);
			y++;
		}
		x++;
	}
	draw_circle(game, 8, (game->player->pos[0] * 20) + 5, (game->player->pos[1] * 20) + 5);
}
*/
// =======================================================================================

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
				my_mlx_pixel_put(game->img, x, y, 0x000089AD);
			else if (isin == 2)
				my_mlx_pixel_put(game->img, x, y, 0x0000000);
			x++;
		}
		y++;
	}
}

int	fabs_minimap(int value)
{
	if (value < 0)
		return (0);
	return (value);
}

int	tabs_minimap(t_game *game, int value, int flg)
{
	if (value > game->map_w && flg == 0)
		return (game->map_w - 1);
	if (value > game->map_h && flg == 1)
		return (game->map_h - 1);
	return (value);
}

void	draw_minimap(t_game *game, t_img *img)
{
	int	pl;
	int	x;
	int	i;
	int	y;
	int	j;

	pl = (MINIMAP / 2) + MINIMAP_S;
	y = fabs_minimap(game->player->pos[1] - 10);
	j = 0;
	while (j < game->map_h)
	{
		i = 0;
		x = fabs_minimap(game->player->pos[0] - 10);
		while (i < game->map_w)
		{
			if (game->map[y][x] == '1')
				draw_square_border(img, 20, (i * 20) + MINIMAP_S, (j * 20) + MINIMAP_S);
			else
				draw_square(img, 20, (i * 20) + MINIMAP_S, (j * 20) + MINIMAP_S);
			i++;
			x++;
		}
		j++;
		y++;
	}
	draw_circle(game, pl, pl, 10);
}
