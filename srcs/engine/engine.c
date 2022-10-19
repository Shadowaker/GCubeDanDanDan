/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:30:32 by dridolfo          #+#    #+#             */
/*   Updated: 2022/10/19 17:42:45 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

double	deg_2_rad(double deg)
{
	return (PI * deg / 180);
}

void	draw_minimap_ray(t_ray *ray, t_game *game, t_img *img)
{
	int		pixels;
	double	dx;
	double	dy;
	double	px;
	double	py;

	dx = (ray->pos[0] - game->player->pos[0]) / ray->delta_dist[0];
	dy = (ray->pos[1] - game->player->pos[1]) / ray->delta_dist[1];
	px = game->player->pos[0] * 20;
	py = game->player->pos[1] * 20;
	pixels = (int) (1);	// meh
	while (pixels)
	{
		my_mlx_pixel_put(img, px + 10, py + 10, 0x00D11131);
		px += dx;
		py += dy;
		pixels--;
	}
}

void	engine(t_game *game, t_img *img, t_ray *ray)
{
	raycast(game, img, ray);
	draw_minimap(game, img);
}
