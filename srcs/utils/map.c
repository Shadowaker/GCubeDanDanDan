/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:58:50 by dridolfo          #+#    #+#             */
/*   Updated: 2022/11/21 15:13:09 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

/*
RETURNS: the length of the string S passed. */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

/*Create an array of arrays, copy the passed array of arrays [MAT]
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

char	**replace_occurence_mat(char **mat, char *stack, char *paste)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	res = ft_calloc(sizeof(char *), ft_matlen(mat));
	while (mat[i] != NULL)
	{
		res[i] = ft_strreplace(mat[i], stack, paste);
		i++;
	}
	res[i] = NULL;
	return (res);
}

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
	map = replace_occurence_mat(map, "\t", "    ");
	print_mat(map);
	free(res);
	return (map);
}
