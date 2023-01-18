/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:57:47 by dridolfo          #+#    #+#             */
/*   Updated: 2023/01/18 16:11:46 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"

void	draw_ray_text(t_ray *ray, int x, int color, t_img *img)
{
	int	v;
	v = 0;
	while (v < ray->draw[0])
	{
		if (!(v >= 10 && v < 210 && ray->ray_id >= 10 && ray->ray_id < 210))
			my_mlx_pixel_put(img, x, v, 0x000089AD);
		v++;
	}
	while (v < ray->draw[1])
	{
		if (!(v >= 10 && v < 210 && ray->ray_id >= 10 && ray->ray_id < 210))
		{
			my_mlx_pixel_put(img, x, v, color);
		}
		v++;
	}
	while (v < WINDOW_H)
	{
		if (!(v >= 10 && v < 210 && ray->ray_id >= 10 && ray->ray_id < 210))
			my_mlx_pixel_put(img, x, v, 0x00403125);
		v++;
	}
}

void	draw_crosshair(t_img *img)
{
	int	i;

	i = 0;
	while (i++ < 15)
		my_mlx_pixel_put(img, (WINDOW_W / 2) + (i * -1), WINDOW_H / 2,  0x00F0F8FF);
	i = 0;
	while (i++ < 15)
		my_mlx_pixel_put(img, (WINDOW_W / 2) + i, WINDOW_H / 2,  0x00F0F8FF);
	i = 0;
	while (i++ < 15)
		my_mlx_pixel_put(img, WINDOW_W / 2, (WINDOW_H / 2) + (i * -1), 0x00F0F8FF);
	i = 0;
	while (i++ < 15)
		my_mlx_pixel_put(img, WINDOW_W / 2, (WINDOW_H / 2) + i, 0x00F0F8FF);
}

unsigned long create_rgb(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}
