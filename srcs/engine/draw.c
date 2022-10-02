/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:31:27 by dridolfo          #+#    #+#             */
/*   Updated: 2022/10/02 17:29:01 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_ray(t_game *game, int x, int y, t_img *img)
{
	int	v;
	v = 0;
	while (v < game->ray->draw[0])
		my_mlx_pixel_put(img, x, v++, 0x000089AD);
	v = y - 1;
	while (v < game->ray->draw[2])
	{
		if (game->ray->side == 1)
			my_mlx_pixel_put(img, x, v++, 0x0040c600 / 2);
		else
			my_mlx_pixel_put(img, x, v++, 0x0040c600);
	}
	while (v < WINDOW_H)
		my_mlx_pixel_put(img, x, v++, 0x00403125);
}
