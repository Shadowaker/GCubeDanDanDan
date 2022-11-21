/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplce.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:28:02 by dridolfo          #+#    #+#             */
/*   Updated: 2022/11/21 14:28:23 by dridolfo         ###   ########.fr       */
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

static int	ft_paste(char *dst, char *src, int start, int size)
{
	int	i;

	i = 0;
	while (start < size && src[i] != '\0')
	{
		dst[start] = src[i];
		start++;
		i++;
	}
	return (i);
}

static void	ft_hack(char **res, char *tmp, int i)
{
	tmp[i] = '\0';
	*res = ft_substr(tmp, 0, i);
	free(tmp);
}

/* Replace a string (stack) contained in a string (src) and paste
another string (paste)
RETURNS: A freeable pointer to the result.*/
char	*ft_strreplace(char const *src, char *stack, char *paste)
{
	int		i;
	int		j;
	char	*res;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(1, STD_SIZE * 10);
	while (src[i] != '\0')
	{
		if (stack != NULL)
		{
			if (src[i] == stack[0])
			{
				if (ft_find(src, i, stack, ft_strlen(stack)) == 1)
				{
					j += ft_paste(tmp, paste, j, STD_SIZE * 10);
					i += ft_strlen(stack);
				}
			}
		}
		tmp[j++] = src[i++];
	}
	ft_hack(&res, tmp, j);
	return (res);
}
