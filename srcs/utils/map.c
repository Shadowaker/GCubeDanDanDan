/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:58:50 by dridolfo          #+#    #+#             */
/*   Updated: 2022/09/30 15:07:39 by dridolfo         ###   ########.fr       */
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

char	*ft_strmerge(char *buff, char *tmp_buff)
{
	size_t	i;
	size_t	j;
	char	*s;

	if (!buff)
	{
		buff = (char *) malloc(1);
		buff[0] = '\0';
	}
	if (!buff || !tmp_buff)
		return (NULL);
	s = malloc((ft_strlen(buff) + ft_strlen(tmp_buff)) + 1);
	if (!s)
		return (NULL);
	i = -1;
	j = 0;
	if (buff)
		while (buff[++i] != '\0')
			s[i] = buff[i];
	while (tmp_buff[j] != '\0')
		s[i++] = tmp_buff[j++];
	s[i] = '\0';
	free(buff);
	return (s);
}

static char	**read_map(int fd)
{
	int		f;
	char	**res;
	char	*buff;
	char	*tmp;

	f = 1;
	tmp = (char *) malloc(2);
	buff = (char *) malloc(2);
	while (f != 0)
	{
		f = read(fd, tmp, 1);
		if (f == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[f] = '\0';
		buff = ft_strmerge(buff, tmp);
	}
	free(tmp);
	res = ft_split(buff, '\n');
	return (res);
}

char	**map_init(char *path)
{
	int		fd;
	char	**map;

	fd = open(path, O_RDONLY);
	map = read_map(fd);
	return (map);
}
