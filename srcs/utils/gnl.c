/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:40:28 by dridolfo          #+#    #+#             */
/*   Updated: 2022/12/03 17:36:41 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

char	*ft_recover(int fd, char *buff)
{
	char	*tmp_buff;
	int		f;

	tmp_buff = (char *) malloc(BUFFER_SIZE + 1);
	if (!tmp_buff)
		return (NULL);
	f = 1;
	while ((ft_find_line(buff) == 0) && f != 0)
	{
		f = read(fd, tmp_buff, BUFFER_SIZE);
		if (f == -1)
		{
			free(tmp_buff);
			return (NULL);
		}
		tmp_buff[f] = '\0';
		buff = ft_strmerge(buff, tmp_buff);
	}
	free(tmp_buff);
	return (buff);
}

/* Read the next line of a file descriptor (FD).
RETURNS: The pointer to a freeable string.*/
char	*get_next_line(int fd)
{
	char		*line;
	static char	*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = ft_recover(fd, buff);
	if (!buff)
		return (NULL);
	line = ft_return_line(buff);
	buff = ft_prepare_next(buff);
	return (line);
}
