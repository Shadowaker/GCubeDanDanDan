/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:42:46 by dridolfo          #+#    #+#             */
/*   Updated: 2022/12/03 18:20:02 by dridolfo         ###   ########.fr       */
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

/* Construct a string with tot (SIZE) characters (C)
RETURNS: A freeable pointer to the new string. */
char	*str_constructor(char c, int size)
{
	char	*res;
	int		i;

	res = malloc(size + 1);
	i = 0;
	while (i < size)
		res[i++] = c;
	res[i] = '\0';
	return (res);
}
