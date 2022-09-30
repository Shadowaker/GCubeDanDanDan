/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:06:47 by dridolfo          #+#    #+#             */
/*   Updated: 2022/09/30 15:07:00 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

/*
Copy a string from START to LEN
RETURNS: a freeable pointer to the result.*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	j;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = (unsigned int) len;
	if (ft_strlen(s) <= len)
		sub = (char *) malloc(ft_strlen(s) + 1);
	else
		sub = (char *)malloc(j + 1);
	if (!sub)
		return (NULL);
	if (!((unsigned int) ft_strlen(s) < start))
	{
		while (s[start] != '\0' && i < j)
		{
			sub[i] = s[start];
			i++;
			start++;
		}
	}
	sub[i] = '\0';
	return (sub);
}

static unsigned int	ft_counter(char const *s, char c)
{
	unsigned int	i;
	unsigned int	con;

	i = 0;
	con = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			con++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (con);
}

static int	ft_strstr(char const *s, char c)
{
	unsigned int	m;

	m = 0;
	while (s[m] != '\0')
	{
		if (s[m] == c)
			return (1);
		m++;
	}
	return (0);
}

static void	ft_looper(char const *s, char **str, char c, unsigned int con)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (k < con)
		{
			str[k] = ft_substr(s, j, (size_t)(i - j));
			k++;
		}
	}
	str[k] = NULL;
}

/* Split an S (char **) using C as separator.
RETURNS: a freeable pointer to the matrix
 (char **) of the result.*/
char	**ft_split(const char *s, char c)
{
	unsigned int	con;
	char			**str;

	if (s == NULL)
		return (NULL);
	con = ft_counter(s, c);
	str = malloc(sizeof(char *) * ((con) + 1));
	if (!str)
		return (NULL);
	if (con == 0)
		str[0] = NULL;
	else if (con == 1 && !ft_strstr(s, c))
	{
		str[0] = ft_substr(s, 0, ft_strlen(s));
		str[1] = NULL;
	}
	else
		ft_looper(s, str, c, con);
	return (str);
}
