/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:36:43 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/27 11:30:26 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"

int	load_text_walls(t_game *game, t_tex *tex, char **path, int pos)
{
	tex->xpm.img = mlx_xpm_file_to_image(game->mlx, path[1],
			&tex->w, &tex->h);
	if (!tex->xpm.img)
		return (1);
	tex->xpm.addr = mlx_get_data_addr(tex->xpm.img,
			&tex->xpm.bits_per_pixel, &tex->xpm.line_length,
			&tex->xpm.endian);
	if (!tex->xpm.addr)
		return (1);
	game->t[pos] = 1;
	return (0);
}

int	load_text(t_game *game, t_tex *tex, char *path)
{
	tex->xpm.img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->w, &tex->h);
	if (!tex->xpm.img)
		return (1);
	tex->xpm.addr = mlx_get_data_addr(tex->xpm.img,
			&tex->xpm.bits_per_pixel, &tex->xpm.line_length,
			&tex->xpm.endian);
	if (!tex->xpm.addr)
		return (1);
	return (0);
}

int	load_door(t_game *game, t_tex *tex, char *path)
{
	return (load_text(game, tex, path));
}
