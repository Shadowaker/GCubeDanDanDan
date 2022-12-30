/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:36:43 by dridolfo          #+#    #+#             */
/*   Updated: 2022/12/30 17:35:10 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"

void	load_text(t_game *game, t_tex *tex, char *path)
{
	tex->xpm.img = mlx_xpm_file_to_image(game->mlx, path,
				&tex->w, &tex->h);
	tex->xpm.addr = mlx_get_data_addr(tex->xpm.img,
				&tex->xpm.bits_per_pixel, &tex->xpm.line_length,
				&tex->xpm.endian);
}

int	get_rgb(char *addr, int x, int y)
{
	int	rgb[3];

	rgb[0] = addr[(x * 4) + (y * 64 * 4) + 2];
	rgb[1] = addr[(x * 4) + (y * 64 * 4) + 1];
	rgb[2] = addr[(x * 4) + (y * 64 * 4)];
	return (0x00FFFFFF & (rgb[0] << 16 | rgb[1] << 8 | rgb[2]));
}

void	load_images(t_game *game)
{
	load_text(game, &(game->texts->wall), PURPLESTONE);
	load_text(game, &(game->texts->wall_side), GREYSTONE);
}

