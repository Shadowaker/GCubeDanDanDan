/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:39:40 by gcucino           #+#    #+#             */
/*   Updated: 2022/10/07 15:42:40 by gcucino          ###   ########.fr       */
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

void	draw_minimap(t_game *game, t_img *img)
{
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
			if (game->map[y][x] == 'N')
				draw_square_border(img, 8, (x * 20) + 16,  (y * 20) + 16);
			y++;
		}
		x++;
	}
}