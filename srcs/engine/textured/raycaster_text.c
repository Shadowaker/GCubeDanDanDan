/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:56:34 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/27 12:00:12 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"

// Initialize ray variables
static void	init_ray(t_game *game, t_ray *ray)
{
	game->player->cam_side = (2.0 * ((double) ray->ray_id)
			/ ((double) WINDOW_W)) - 1;
	ray->dir[0] = game->player->dir[0]
		+ game->player->cam_plane[0] * game->player->cam_side;
	ray->dir[1] = game->player->dir[1]
		+ game->player->cam_plane[1] * game->player->cam_side;
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
}

// Calculate the direction of the ray.
static void	calc_incr(t_game *game, t_ray *ray)
{
	if (ray->dir[0] < 0)
	{
		ray->incr[0] = -1;
		ray->side_dist[0] = (game->player->pos[0]
				- ((double) ray->pos[0])) * ray->delta_dist[0];
	}
	else
	{
		ray->incr[0] = 1;
		ray->side_dist[0] = (((double) ray->pos[0]) + 1.0
				- game->player->pos[0]) * ray->delta_dist[0];
	}
	if (ray->dir[1] < 0)
	{
		ray->incr[1] = -1;
		ray->side_dist[1] = (game->player->pos[1]
				- ((double) ray->pos[1])) * ray->delta_dist[1];
	}
	else
	{
		ray->incr[1] = 1;
		ray->side_dist[1] = (((double) ray->pos[1]) + 1.0
				- game->player->pos[1]) * ray->delta_dist[1];
	}
}

// Set variables needed to draw the ray.
static void	init_draw(t_game *game, t_ray *ray)
{
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
}

/*
	wallx	-> where exactly the wall was hit
	texx	-> x coordinate on the texture
	step	-> How much to increase the texture coordinate per screen pixel
	texpos	-> Starting texture coordinate
*/
static void	init_wall_vars(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wallx = game->player->pos[1] + ray->wall_dist * ray->dir[1];
	else
		ray->wallx = game->player->pos[0] + ray->wall_dist * ray->dir[0];
	ray->wallx -= floor(ray->wallx);
	ray->texx = (int)(ray->wallx * 64.0);
	if (ray->side == 0 && ray->dir[0] > 0)
		ray->texx = 64 - ray->texx - 1;
	if (ray->side == 1 && ray->dir[1] < 0)
		ray->texx = 64 - ray->texx - 1;
	ray->step = 1.0 * 64.0 / ((double) ray->wall_height);
	ray->texpos = (((double) ray->draw[0]) - WINDOW_H / 2
			+ ray->wall_height / 2) * ray->step;
}

// Cast the ray.
int	raycast_text(t_game *game, t_img *img, t_ray *ray)
{
	int		i;
	double	zbuffer[WINDOW_W];

	i = 0;
	while (i < WINDOW_W)
	{
		ray->ray_id = i;
		init_ray(game, ray);
		calc_incr(game, ray);
		dda(game, ray);
		init_draw(game, ray);
		init_wall_vars(game, ray);
		draw_ray_text(game, i, ray, img);
		zbuffer[i] = ray->wall_dist;
		i++;
	}
	draw_sprites(game, zbuffer);
	draw_crosshair(img);
	return (0);
}
