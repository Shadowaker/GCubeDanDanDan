/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:58:50 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/28 15:06:08 by dridolfo         ###   ########.fr       */
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
			map[i] = ft_freejoin(map[i],
					str_constructor(' ', size[1] - size[0]));
		i++;
	}
}

/* Init the passed game map.
RETURNS: A freeable pointer to the game map.*/
int	map_init(t_game *game, int fd)
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
	free(res);
	game->map = map;
	return (0);
}
