/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:15:50 by dridolfo          #+#    #+#             */
/*   Updated: 2022/11/20 17:09:56 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

int	first_recurrence(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
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
	while (i >= 0)
	{
		if (c == str[i])
			return (i);
		i--;
	}
	return (-1);
}

int	last_repeat(char *str, int start, char c)
{
	while (str[start] != '\0' && str[start] != 'c')
		start++;
	return (start);
}

int first_to_last(char *str, int *left, int *right)
{
	*left = first_recurrence(str, '1');
	if (*left == -1)
		return (1);
	while (str[*left] != '\0' && str[*left] == '1')
		(*left)++;
	*right = first_recurrence(str, '1');
	if (*right == -1)
		return (1);
	while (*right >= *left && str[*right] == '1')
		(*right)--;
	return (0);
}

int	map_validator(char **map)
{
	int	i;
	int	o_left;
	int	o_right;
	int	left;
	int	right;

	i = 1;
	if (first_to_last(map[0], &left, &o_right) == -1)
		return (1);
	o_left = last_repeat(map[0], left, 'c');
	while (map[i] != NULL)
	{
		if (first_to_last(map[i], &left, &right) == -1)
			return (1);
		if (left < o_left || right > o_right)
			return (1);
		o_left = left;
		o_right = right;
		i++;
	}
	return (0);
}
