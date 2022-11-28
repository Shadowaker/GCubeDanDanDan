/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:15:50 by dridolfo          #+#    #+#             */
/*   Updated: 2022/11/28 19:03:56 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

int	first_recurrence(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str != NULL)
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (-1);
}

int last_recurrence(char *str, char c)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0 && str != NULL)
	{
		if (c == str[i])
			return (i);
		i--;
	}
	return (-1);
}

int first_to_last(char *str, int *left, int *right)
{
	left[1] = first_recurrence(str, '1');
	if (left[1] == -1)
		return (-1);
	while (str[++left[1]] != '\0' && str[left[1]] == '1')
		;
	--left[1];
	right[1] = last_recurrence(str, '1');
	if (right[1] == -1)
		return (-1);
	while (++right[1] >= *left && str[right[1]] == '1')
		;
	--right[1];
	return (0);
}

int	next_to(char *str, int start, int end, char c)
{
	int	i;

	i = start;
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (i != end && str[i] != '\0')
		return (1);
	return (0);
}

int	map_validator(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{

	}
	return (0);
}
