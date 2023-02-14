/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:57:44 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/14 11:59:37 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

/* */
int	parse_error(int fd, char *tobefreed)
{
	close(fd);
	free(tobefreed);
	return (1);
}

/*
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
	while (i < 4)
	{
		line = get_next_line(fd);
		line[ft_strlen(line) - 1] = '\0';
		if (load_image(game, texts, line) || !line)
			return (parse_error(fd, line));
		free(line);
		i++;
	}
	line = get_next_line(fd);
	if (!line)
		return (parse_error(fd, line));
	free(line);
	i = 0;
	while (i < 2)
	{
		line = get_next_line(fd);
		if (load_rgb(game, line) || !line)
			return (parse_error(fd, line));
		free(line);
		i++;
	}
	line = get_next_line(fd);
	if (map_init_(game, fd) || !line)
		return (parse_error(fd, line));
	free(line);
	close(fd);
	return (0);
}
