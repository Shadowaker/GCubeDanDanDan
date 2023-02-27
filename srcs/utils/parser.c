/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:57:44 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/27 11:31:14 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

/*
	Return an error and exit safely. */
static int	parse_error(int fd, char *tobefreed)
{
	close(fd);
	free(tobefreed);
	return (1);
}

static int	filter(t_game *game, t_textures *texts, char **split)
{
	if (!ft_strcmp(split[0], "NO"))
		return (load_text_walls(game, &(texts->no), split, 0));
	else if (!ft_strcmp(split[0], "SO"))
		return (load_text_walls(game, &(texts->so), split, 1));
	else if (!ft_strcmp(split[0], "WE"))
		return (load_text_walls(game, &(texts->we), split, 2));
	else if (!ft_strcmp(split[0], "EA"))
		return (load_text_walls(game, &(texts->ea), split, 3));
	else if (!ft_strcmp(split[0], "F"))
		return (load_rgb_utils(game, split, 'F', 4));
	else if (!ft_strcmp(split[0], "C"))
		return (load_rgb_utils(game, split, 'C', 5));
	return (1);
}

static int	gcheck(int *t)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (t[i] != 1)
			return (0);
		i++;
	}
	return (1);
}

static int	parserino(t_game *game, t_textures *texts, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (ft_matlen(split) != 2)
	{
		free_mat(split);
		return (1);
	}
	split[1][ft_strlen(split[1]) - 1] = '\0';
	if (filter(game, texts, split))
	{
		free_mat(split);
		return (1);
	}
	free_mat(split);
	return (0);
}

int	parser(t_game *game, t_textures *texts, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	line = NULL;
	while (!gcheck(game->t))
	{
		line = get_next_line(fd);
		if (!line)
			return (parse_error(fd, NULL));
		if (!ft_strcmp(line, "\n"))
		{
			free(line);
			continue ;
		}
		if (parserino(game, texts, line))
			return (parse_error(fd, line));
		free(line);
	}
	if (map_init(game, fd) || !line)
		return (parse_error(fd, line));
	return (0);
}
