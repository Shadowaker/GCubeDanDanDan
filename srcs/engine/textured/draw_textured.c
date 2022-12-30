/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:57:47 by dridolfo          #+#    #+#             */
/*   Updated: 2022/12/30 13:43:42 by dridolfo         ###   ########.fr       */
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
