/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:36:43 by dridolfo          #+#    #+#             */
/*   Updated: 2023/01/18 16:08:18 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"


static int	load_text(t_game *game, t_tex *tex, char **path)
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

static int	load_text2(t_game *game, t_tex *tex, char *path)
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
		return(load_text(game, &(texts->no), s));
	else if (!ft_strcmp(s[0], "SO"))
		return(load_text(game, &(texts->so), s));
	else if (!ft_strcmp(s[0], "WE"))
		return(load_text(game, &(texts->we), s));
	else if (!ft_strcmp(s[0], "EA"))
		return(load_text(game, &(texts->ea), s));
	free_mat(s);
	return (1);
}

void	load_images(t_game *game)
{
	load_text2(game, &(game->texts->wall), PURPLESTONE);
	load_text2(game, &(game->texts->wall_side), GREYSTONE);
}

int	get_rgb(char *addr, int x, int y)
{
	int	rgb[3];

	rgb[0] = addr[(x * 4) + (y * 64 * 4) + 2];
	rgb[1] = addr[(x * 4) + (y * 64 * 4) + 1];
	rgb[2] = addr[(x * 4) + (y * 64 * 4)];
	return (0x00FFFFFF & (rgb[0] << 16 | rgb[1] << 8 | rgb[2]));
}

int	load_rgb(t_game *game, char *line)
{
	int		i;
	char	**s;
	char	**rgbb;

	s = ft_split(line, ' ');
	if (ft_matlen(s) != 2)
	{
		free_mat(s);
		return (1);
	}
	if (!ft_strcmp(s[0], "F"))
	{
		rgbb = ft_split(s[1], ',');
		if (ft_matlen(rgbb) != 3)
		{
			free_mat(s);
			free_mat(rgbb);
			return (1);
		}
		i = -1;
		while (i++ < 2)
			game->f[i] = ft_atoi(rgbb[i]);
		free_mat(rgbb);
	}
	if (!ft_strcmp(s[0], "C"))
	{
		rgbb = ft_split(s[1], ',');
		if (ft_matlen(rgbb) != 3)
		{
			free_mat(s);
			free_mat(rgbb);
			return (1);
		}
		i = -1;
		while (i++ < 2)
			game->c[i] = ft_atoi(rgbb[i]);
		free_mat(rgbb);
	}
	free_mat(s);
	return (0);
}

