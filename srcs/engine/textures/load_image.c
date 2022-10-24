/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:36:43 by dridolfo          #+#    #+#             */
/*   Updated: 2022/10/24 14:26:52 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"

void	load_images(t_game *game)
{
	t_tex	wall;
	t_tex	wall_side;

	wall.xpm.img = mlx_xpm_file_to_image(game->mlx, PURPLESTONE,
				&wall.w, &wall.h);
	wall_side.xpm.addr = mlx_get_data_addr(wall.xpm.img,
				&wall.xpm.bits_per_pixel, &wall.xpm.line_length,
				&wall.xpm.endian);
	game->texts->wall = &wall;
	wall_side.xpm.img = mlx_xpm_file_to_image(game->mlx, PURPLESTONE,
				&wall_side.w, &wall_side.h);
	wall_side.xpm.addr = mlx_get_data_addr(wall_side.xpm.img,
				&wall_side.xpm.bits_per_pixel, &wall_side.xpm.line_length,
				&wall_side.xpm.endian);
	game->texts->wall_side = &wall_side;
}
