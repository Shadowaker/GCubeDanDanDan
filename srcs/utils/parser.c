/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:57:44 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/14 13:06:01 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

/*
	Return an error and exit safely. */
int	parse_error(int fd, char *tobefreed)
{
	close(fd);
	free(tobefreed);
	return (1);
}

static void	parserino(t_game *game, t_textures *texts, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (i < 4)
	{
		line = get_next_line(fd);
		if (!line)
			return (parse_error(fd, line));
		line[ft_strlen(line) - 1] = '\0';
		if (load_image(game, texts, line) || !line)
			return (parse_error(fd, line));
		free(line);
		i++;
	}
}

static void parserone(t_game *game, t_textures *texts, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (i < 2)
	{
		line = get_next_line(fd);
		if (!line)
			return (parse_error(fd, line));
		if (load_rgb(game, line) || !line)
			return (parse_error(fd, line));
		free(line);
		i++;
	}
}

/*
	Parse map given as input and return 0 on success.
RETURNS: 0 on success, 1 otherwise.
*/
int parser(t_game *game, t_textures *texts, char *path)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);

	parserino(game, texts, fd);
	line = get_next_line(fd);
	if (!line)
		return (parse_error(fd, line));
	free(line);
	parserone(game, texts, fd);
	line = get_next_line(fd);
	if (map_init(game, fd) || !line)
		return (parse_error(fd, line));
	free(line);
	close(fd);
	return (0);
}
