/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:56:34 by dridolfo          #+#    #+#             */
/*   Updated: 2023/01/23 18:33:14 by dridolfo         ###   ########.fr       */
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

//	DDA Algorithm.
static void	dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	if (game->map[(ray->pos[1])][(ray->pos[0])] == '1')
	{
		if (ray->side_dist[0] < ray->side_dist[1])
			ray->side = 0;
		else
			ray->side = 1;
		return ;
	}
	while (hit == 0)
	{
		if (ray->side_dist[0] < ray->side_dist[1])
		{
			ray->side_dist[0] += ray->delta_dist[0];
			ray->pos[0] += ray->incr[0];
			ray->side = 0;
		}
		else
		{
			ray->side_dist[1] += ray->delta_dist[1];
			ray->pos[1] += ray->incr[1];
			ray->side = 1;
		}
		if (game->map[(ray->pos[1])][(ray->pos[0])] == '1')
			hit = 1;
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

unsigned int	get_pixel(t_img *img, int x, int y)
{
	char	*dest;

	if (x <= 0 || x >= 64 || y < 0 || y >= 64)
		return (1);
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dest);
}

// Cast the ray. (NS)
int	raycast_text(t_game *game, t_img *img, t_ray *ray)
{
	int	i;

	i = 0;
	while (i < WINDOW_W)
	{
		ray->ray_id = i;
		init_ray(game, ray);
		if (ray->dir[0] == 0)
			ray->delta_dist[0] = 1e30;
		else
			ray->delta_dist[0] = absf(1.0 / ray->dir[0]);
		if (ray->dir[1] == 0)
			ray->delta_dist[1] = 1e30;
		else
			ray->delta_dist[1] = absf(1.0 / ray->dir[1]);
		calc_incr(game, ray);
		dda(game, ray);
		init_draw(game, ray);

		double wallX; //where exactly the wall was hit
		if (ray->side == 0)
			wallX = game->player->pos[1] + ray->wall_dist * ray->dir[1];
		else
			wallX = game->player->pos[0] + ray->wall_dist * ray->dir[0];
		wallX -= floor(wallX);

		//x coordinate on the texture
		int texX = (int) (wallX * 64.0);
		if(ray->side == 0 && ray->dir[0] > 0)
			texX = 64 - texX - 1;
		if(ray->side == 1 && ray->dir[1] < 0)
			texX = 64 - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * 64.0 / ((double) ray->wall_height);
		// Starting texture coordinate
		double texPos = (((double) ray->draw[0]) - WINDOW_H / 2 + ray->wall_height / 2) * step;

		int	v;
		v = 0;
		while (v < ray->draw[0])
		{
			my_mlx_pixel_put(img, i, v, create_rgb(game->f[0], game->f[1], game->f[2]));
			v++;
		}

		int color = 0;
		v = ray->draw[0];
		while (v < ray->draw[1])
		{
			int texY = (int) texPos & (64 - 1);
			texPos += step;
			if (ray->side == 1)
				color = get_pixel(&game->texts->wall_side.xpm, texX, texY);
			else
				color = get_pixel(&game->texts->wall.xpm, texX, texY);
			my_mlx_pixel_put(img, i, v, color);
			v++;
		}

		while (v < WINDOW_H)
		{
			my_mlx_pixel_put(img, i, v, create_rgb(game->c[0], game->c[1], game->c[2]));
			v++;
		}
		i++;
	}

	draw_crosshair(img);

	return (0);
}
