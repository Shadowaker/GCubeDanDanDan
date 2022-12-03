/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:28:02 by dridolfo          #+#    #+#             */
/*   Updated: 2022/12/03 16:37:54 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

static int	ft_find(char const *s1, int start, char *s2, int size)
{
	int	i;

	i = 0;
	while (i < size && s1[start] != '\0')
	{
		if (s1[start] != s2[i])
			return (0);
		i++;
		start++;
	}
	if (s1[start] != s2[i] && s1[start] == '\0')
		return (0);
	return (1);
}

static char	*createstr(char c)
{
	char	*res;

	res = ft_calloc(1, 2);
	res[0] = c;
	return (res);
}

/* Replace a string (STACK) contained in a string (SRC) and paste
	another string (PASTE).
	If SRC, STACK or PASTE are == NULL, behavior is undefined.
RETURNS: A freeable pointer to the result.*/
char	*ft_strreplace(char const *src, char *stack, char *paste)
{
	int		i;
	char	*tmp;

	tmp = ft_calloc(1, 1);
	i = 0;
	while (src[i] != '\0')
	{
		if (ft_find(src, i, stack, ft_strlen(stack)))
		{
			tmp = ft_freejoin(tmp, ft_substr(paste, 0, ft_strlen(paste)));
			i += ft_strlen(stack);
		}
		else
			tmp = ft_freejoin(tmp, createstr(src[i++]));
	}
	return (tmp);
}
