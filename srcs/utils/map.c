/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:58:50 by dridolfo          #+#    #+#             */
/*   Updated: 2022/11/18 19:30:30 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

/*
RETURNS: the S length.*/
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

char	**replace_occurence_mat(char **mat)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
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
	print_mat(map);
	free(res);
	return (map);
}
