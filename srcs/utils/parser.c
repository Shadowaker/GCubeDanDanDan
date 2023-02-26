/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:57:44 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/26 19:13:19 by dridolfo         ###   ########.fr       */
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

/*
	Parse map given as input and return 0 on success.
RETURNS: 0 on success, 1 otherwise.
*/
int	parser(t_game *game, t_textures *texts, char *path)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	//parserino(game, texts, fd);
	line = get_next_line(fd);
	if (!line)
		return (parse_error(fd, line));
	free(line);
	//parserone(game, texts, fd);
	line = get_next_line(fd);
	if (map_init(game, fd) || !line)
		return (parse_error(fd, line));
	free(line);
	close(fd);
	return (0);
}

static int	filter(t_game *game, t_textures *texts, char **split)
{
	if (ft_strcmp(split[0], "NO"))
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

int	miniparser(t_game *game, t_textures *texts, int fd)
{
	static int	i = 0;
	char		*line;
	char		**split;
	char		*tmp;

	line = get_next_line(fd);
	while (!ft_strcmp(line, "\n"))
	{
		free(line);
		line = get_next_line(fd);
	}
	split = ft_split(line, ' ');
	tmp = split[1];
	split[1] = ft_strreplace(split[1], "\n", "");
	free(tmp);
	if (ft_matlen(split) != 2)
	{
		printf("culo");
		free_mat(split);
		return(parse_error(fd, line));
	}
	if (filter(game, texts, split))
	{
		culo(NULL);
		free_mat(split);
		return(parse_error(fd, line));
	}
	free_mat(split);
	return (0);
}

int	gcheck(int *t)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (t[i] != 1)
			return (1);
		i++;
	}
	return (0);
}

int	newparser(t_game *game, t_textures *texts, char *path)
{
	int	fd;
	int	i;

	i = 0;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	while (miniparser(game, texts, fd) != 1)
		i++;
	if (i != 6 && gcheck(game->t))
	{
		printf("i: %d\n", i);
		close(fd);
		return(1);
	}
	return (0);
}
