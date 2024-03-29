/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:31:27 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/15 15:26:46 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	draw_ray_minimap(t_ray *ray, int x, t_img *img)
{
	int	v;

	v = -1;
	while (v < ray->draw[0])
	{
		if (v < 10 || v >= 210)
			my_mlx_pixel_put(img, x, v, 0x000089AD);
		v++;
	}
	while (v < ray->draw[1])
	{
		if (v < 10 || v >= 210)
		{
			if (ray->side == 1)
				my_mlx_pixel_put(img, x, v++, 0x0040c600 / 2);
			else
				my_mlx_pixel_put(img, x, v++, 0x0040c600);
		}
		v++;
	}
	while (v < WINDOW_H)
		my_mlx_pixel_put(img, x, v++, 0x00403125);
}

void	draw_ray(t_ray *ray, int x, int y, t_img *img)
{
	int	v;

	v = -1;
	while (++v < ray->draw[0])
	{
		if (!(v >= 10 && v < 210 && ray->ray_id >= 10 && ray->ray_id < 210))
			my_mlx_pixel_put(img, x, v, 0x000089AD);
	}
	while (v < ray->draw[1])
	{
		if (!(v >= 10 && v < 210 && ray->ray_id >= 10 && ray->ray_id < 210))
		{
			if (ray->side == 1)
				my_mlx_pixel_put(img, x, v, 0x0040c600 / 2);
			else
				my_mlx_pixel_put(img, x, v, 0x0040c600);
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
