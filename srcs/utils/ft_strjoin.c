/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:26:52 by dridolfo          #+#    #+#             */
/*   Updated: 2022/10/03 15:27:00 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

/* Join two strings.
RETURNS: a freeable pointer to the result.*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	j = ft_strlen(s1);
	str = malloc(j + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < j)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

/* Join two strings with a separator in the middle.
RETURNS: a freeable pointer to the result.*/
char	*ft_dotjoin(char const *s1, char const *s2, char *sep)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	j = ft_strlen(s1);
	str = malloc(j + ft_strlen(sep) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < j)
		str[i] = s1[i];
	j = -1;
	while (sep[++j] != '\0')
		str[i++] = sep[j];
	j = 0;
	while (j < ft_strlen(s2))
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

/* Join two strings and free them.
RETURNS: a freeable pointer to the result. */
char	*ft_freejoin(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}
