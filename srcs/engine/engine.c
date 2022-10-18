/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:30:32 by dridolfo          #+#    #+#             */
/*   Updated: 2022/10/18 12:17:27 by dridolfo         ###   ########.fr       */
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
	pixels = (int) (ray->dist);
	while (pixels)
	{
		my_mlx_pixel_put(img, px + 10, py + 10, 0x00D11131);
		px += dx;
		py += dy;
		pixels--;
	}
}

int	raycast(t_game *game, t_img *img, t_ray *ray)
{
	int	i;

	i = 0;
	//draw_minimap(game, img);
	while (i < WINDOW_W)
	{
		game->player->cam_side = (2.0 * ((double) i) / ((double) WINDOW_W)) - 1;

		ray->ray_id = i;
		ray->dir[0] = game->player->dir[0] + game->player->cam_plane[0] * game->player->cam_side;
		ray->dir[1] = game->player->dir[1] + game->player->cam_plane[1] * game->player->cam_side;

		ray->pos[0] = (int) game->player->pos[0];
		ray->pos[1] = (int) game->player->pos[1];

		if (ray->dir[0] == 0)
			ray->delta_dist[0] = 1e30;
		else
			ray->delta_dist[0] = absf(1.0 / ray->dir[0]);
		if (ray->dir[1] == 0)
			ray->delta_dist[1] = 1e30;
		else
			ray->delta_dist[1] = absf(1.0 / ray->dir[1]);

		int		incr[2];
		int		hit;

		if (ray->dir[0] < 0)
		{
			incr[0] = -1;
			ray->side_dist[0] = (game->player->pos[0] - ((double) ray->pos[0])) * ray->delta_dist[0];
		}
		else
		{
			incr[0] = 1;
			ray->side_dist[0] = (((double) ray->pos[0]) + 1.0 - game->player->pos[0]) * ray->delta_dist[0];
		}
		if (ray->dir[1] < 0)
		{
			incr[1] = -1;
			ray->side_dist[1] = (game->player->pos[1] - ((double) ray->pos[1])) * ray->delta_dist[1];
		}
		else
		{
			incr[1] = 1;
			ray->side_dist[1] = (((double) ray->pos[1]) + 1.0 - game->player->pos[1]) * ray->delta_dist[1];
		}
		hit = 0;
		ray->dist = 0;
		while (hit == 0)
		{
			if (ray->side_dist[0] < ray->side_dist[1])
			{
				ray->side_dist[0] += ray->delta_dist[0];
				ray->pos[0] += incr[0];
				ray->side = 0;
			}
			else
			{
				ray->side_dist[1] += ray->delta_dist[1];
				ray->pos[1] += incr[1];
				ray->side = 1;
			}
			ray->dist += 1;
			if (game->map[(ray->pos[1])][(ray->pos[0])] == '1')
				hit = 1;
		}
		if (ray->side == 0)
			ray->wall_dist = ray->side_dist[0] - ray->delta_dist[0];
		else
			ray->wall_dist = ray->side_dist[1] - ray->delta_dist[1];

		ray->wall_height = (int) WINDOW_H / (ray->wall_dist);
		ray->draw[0] = (WINDOW_H / 2) - (ray->wall_height / 2);
		ray->draw[1] = (WINDOW_H / 2) + (ray->wall_height / 2);

		if (ray->draw[0] < 0)
			ray->draw[0] = 0;
		if (ray->wall_dist <= 0)
		{
			ray->wall_height = WINDOW_H;
			ray->wall_dist = 0;
		}
		if (ray->draw[1] >= WINDOW_H)
			ray->draw[1] = WINDOW_H - 1;
		//if (i < 10 || i >= 210)
		draw_ray(ray, i, 0, img);
		//else
		//	draw_ray_minimap(ray, i, img);
		//draw_minimap_ray(ray, game, img);
		i++;
	}
	return (0);
}
