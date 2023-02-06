/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:36:43 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/06 16:47:24 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"


static int	load_text_walls(t_game *game, t_tex *tex, char **path)
{
	tex->xpm.img = mlx_xpm_file_to_image(game->mlx, path[1],
				&tex->w, &tex->h);
	free_mat(path);
	if (!tex->xpm.img)
		return (1);
	tex->xpm.addr = mlx_get_data_addr(tex->xpm.img,
				&tex->xpm.bits_per_pixel, &tex->xpm.line_length,
				&tex->xpm.endian);
	if (!tex->xpm.addr)
		return (1);
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

int	load_image(t_game *game, t_textures *texts, char *path)
{
	char	**s;

	if (!path)
		return (1);
	s = ft_split(path, ' ');
	if (ft_matlen(s) != 2)
	{
		free_mat(s);
		return (1);
	}
	if (!ft_strcmp(s[0], "NO"))
		return(load_text_walls(game, &(texts->no), s));
	else if (!ft_strcmp(s[0], "SO"))
		return(load_text_walls(game, &(texts->so), s));
	else if (!ft_strcmp(s[0], "WE"))
		return(load_text_walls(game, &(texts->we), s));
	else if (!ft_strcmp(s[0], "EA"))
		return(load_text_walls(game, &(texts->ea), s));
	free_mat(s);
	return (1);
}

// To be deleted
void	load_images(t_game *game)
{
	load_text(game, &(game->texts->wall), PURPLESTONE);
	load_text(game, &(game->texts->wall_side), GREYSTONE);
}

