/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:57:47 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/27 11:58:35 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"

static void	draw_ceiling(t_game *game, int x, t_ray *ray, t_img *img)
{
	int	v;

	v = 0;
	while (v < ray->draw[0])
	{
		my_mlx_pixel_put(img, x, v,
			create_rgb(game->f[0], game->f[1], game->f[2]));
		v++;
	}
}

static void	draw_flooring(t_game *game, int x, t_ray *ray, t_img *img)
{
	int	v;

	v = ray->draw[1];
	while (v < WINDOW_H)
	{
		my_mlx_pixel_put(img, x, v,
			create_rgb(game->c[0], game->c[1], game->c[2]));
		v++;
	}
}

static unsigned long int	get_color(t_game *game, t_ray *ray, int texy)
{
	unsigned long int	color;

	color = 0;
	if (game->map[(ray->pos[1])][(ray->pos[0])] == 'D')
		color = get_pixel(&game->texts->door.xpm, ray->texx, texy);
	else if (ray->side == 0)
	{
		if (game->player->pos[0] - ray->pos[0] > 0)
			color = get_pixel(&game->texts->we.xpm, ray->texx, texy);
		else
			color = get_pixel(&game->texts->ea.xpm, ray->texx, texy);
	}
	else
	{
		if (game->player->pos[1] - ray->pos[1] > 0)
			color = get_pixel(&game->texts->no.xpm, ray->texx, texy);
		else
			color = get_pixel(&game->texts->so.xpm, ray->texx, texy);
	}
	return (color);
}

void	draw_ray_text(t_game *game, int x, t_ray *ray, t_img *img)
{
	int					v;
	unsigned long int	color;
	int					texy;

	draw_ceiling(game, x, ray, img);
	v = ray->draw[0];
	color = 0;
	while (v < ray->draw[1])
	{
		texy = (int) ray->texpos & (64 - 1);
		ray->texpos += ray->step;
		color = get_color(game, ray, texy);
		my_mlx_pixel_put(img, x, v, color);
		v++;
	}
	draw_flooring(game, x, ray, img);
}

void	draw_crosshair(t_img *img)
{
	int	i;

	i = 0;
	while (i++ < 20)
		my_mlx_pixel_put(img, (WINDOW_W / 2) + (i * -1), WINDOW_H / 2,
			0x00F0F8FF);
	i = 0;
	while (i++ < 20)
		my_mlx_pixel_put(img, (WINDOW_W / 2) + i, WINDOW_H / 2, 0x00F0F8FF);
	i = 0;
	while (i++ < 20)
		my_mlx_pixel_put(img, WINDOW_W / 2, (WINDOW_H / 2) + (i * -1),
			0x00F0F8FF);
	i = 0;
	while (i++ < 20)
		my_mlx_pixel_put(img, WINDOW_W / 2, (WINDOW_H / 2) + i, 0x00F0F8FF);
}
