/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revmat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:49:20 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/14 11:30:16 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

char	**ft_revmat(char **mat)
{
	char	**res;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = ft_matlen(mat);
	res = malloc(j + 1);
	j--;
	while (j > 0)
	{
		tmp = ft_strreverse(mat[j--]);
		res[i++] = tmp;
	}
	res[i] = NULL;
	return (res);
}
