/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:58:50 by dridolfo          #+#    #+#             */
/*   Updated: 2022/09/30 19:11:38 by dridolfo         ###   ########.fr       */
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

char	**map_init(char *path)
{
	int		fd;
	char	*str;
	char	**map;

	fd = open(path, O_RDONLY);
	str = get_next_line(fd);
	if (str != NULL)
		str[ft_strlen(str) - 1] = '\0';
	map = malloc(sizeof(char *) * 1);
	map[0] = NULL;
	while (str != NULL)
	{
		map = expand_mat(map, str);
		str = get_next_line(fd);
		if (str != NULL)
			str[ft_strlen(str) - 1] = '\0';
	}
	close(fd);
	return (map);
}
