/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:58:50 by dridolfo          #+#    #+#             */
/*   Updated: 2023/01/18 15:55:28 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

/* Create an array of arrays, copy the passed array of arrays [MAT]
	and add at the end the passed string [STR].
	Then free the orginal array of arrays.
RETURNS: The new array of arrays.*/
char	**expand_mat(char **mat, char *str)
{
	int		len;
	char	**res;

	len = ft_matlen(mat);
	res = malloc(sizeof(char *) * (len + 2));
	ft_cpmat(mat, res, 0);
	res[len] = str;
	res[len + 1] = NULL;
	free(mat);
	return (res);
}

/* Replace any occurrence of STACK in every array of a matrix (MAT)
	and replace it with PASTE.
RETURNS: */
void	replace_occurence_mat(char **mat, char *stack, char *paste)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (mat[i] != NULL)
	{
		tmp = mat[i];
		mat[i] = ft_strreplace(tmp, stack, paste);
		free(tmp);
		i++;
	}
}

static void	map_format(char **map)
{
	int		i;
	int		size[2];

	i = 0;
	size[1] = 0;
	while (map[i] != NULL)
	{
		size[0] = ft_strlen(map[i]);
		if (size[1] < size[0])
			size[1] = size[0];
		i++;
	}
	i = 0;
	while (map[i] != NULL)
	{
		size[0] = ft_strlen(map[i]);
		if (size[0] < size[1])
			map[i] = ft_freejoin(map[i], str_constructor(' ', size[1] - size[0]));
		i++;
	}
}

/* Init the passed map in file (PATH) and format it to the
	standard array of arrays of chars.
RETURNS: A freeable pointer to the game map.*/
char	**map_init(char *path)
{
	int		fd;
	char	*str;
	char	*res;
	char	**map;

	fd = open(path, O_RDONLY);
	str = get_next_line(fd);
	res = malloc(1);
	res[0] = '\0';
	if (str != NULL)
		str[ft_strlen(str)] = '\0';
	while (str != NULL)
	{
		res = ft_freejoin(res, str);
		str = get_next_line(fd);
	}
	close(fd);
	map = ft_split(res, '\n');
	replace_occurence_mat(map, "\t", "    ");
	map_format(map);
	print_mat(map, '@');
	free(res);
	printf("\n\n");
	return (map);
}

int		map_init_(t_game *game, int fd)
{
	char	*str;
	char	*res;
	char	**map;

	str = get_next_line(fd);
	res = malloc(1);
	res[0] = '\0';
	if (str != NULL)
		str[ft_strlen(str)] = '\0';
	while (str != NULL)
	{
		res = ft_freejoin(res, str);
		str = get_next_line(fd);
	}
	map = ft_split(res, '\n');
	replace_occurence_mat(map, "\t", "    ");
	map_format(map);
	print_mat(map, '@');
	free(res);
	game->map = map;
	return (0);
}

int	parse_error(int fd, char *tobefreed)
{
	close(fd);
	free(tobefreed);
	return (1);
}

int parser(t_game *game, t_textures *texts, char *path)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(path, O_RDONLY);
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
