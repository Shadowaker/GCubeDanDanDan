/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:42:46 by dridolfo          #+#    #+#             */
/*   Updated: 2022/12/03 17:47:34 by dridolfo         ###   ########.fr       */
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

/*
RETURNS: 0 if C not in STACK else 1. */
int	ft_isinstr(const char *stack, char c)
{
	int	i;

	i = 0;
	if (stack == NULL)
		return (0);
	while (stack[i] != '\0')
	{
		if (stack[i] == c)
			return (1);
		i++;
	}
	return (0);
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
