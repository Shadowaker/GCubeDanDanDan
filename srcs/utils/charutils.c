/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:19:13 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/15 17:33:00 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

/* Find the coordinates (IDS) of a char c in an array
	of arrays (map).
	If the char was not found the coords will be negative.
RETURNS: */
void	find_char(char **map, int *ids)
{
	ids[1] = 0;
	while (map[ids[1]] != NULL)
	{
		ids[0] = 0;
		while (map[ids[1]][ids[0]] != '\0')
		{
			if (ft_isinstr("NSWE", map[ids[1]][ids[0]]))
				return ;
			ids[0]++;
		}
		ids[1]++;
	}
	ids[1] = -1;
	ids[0] = -1;
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
