/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:57:47 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/13 17:46:07 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"

unsigned long	get_pixel(t_img *img, int x, int y)
{
	char	*dest;

	if (x < 0 || x >= 64 || y < 0 || y >= 64)
		return (1);
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned long *)dest);
}

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
