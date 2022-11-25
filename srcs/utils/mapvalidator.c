/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:15:50 by dridolfo          #+#    #+#             */
/*   Updated: 2022/11/25 14:52:16 by dridolfo         ###   ########.fr       */
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
	//printf("left: %d	right: %d\n", left[1], right[1]);
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
	int	left[2];
	int	right[2];
	int	max;

	i = 1;
	max = ft_matlen(map) - 1;
	if (first_to_last(map[0], left, right) == -1)
	{
		printf("Culo 1 - %d\n", i);
		return (-1);
	}
	if (next_to(map[0], first_recurrence(map[i], '1'),
		last_recurrence(map[i], '1'), '1') == 0)
	{
		printf("Culo 2 - %d\n", i);
		return (-1);
	}
	left[0] = left[1];
	right[0] = left[1];
	while (i < max)
	{
		printf("------------------- %d \n", i);
		printf("left 0: %d	right 0: %d\n", left[0], right[0]);
		printf("left 1: %d	right 1: %d\n", left[1], right[1]);
		if (first_to_last(map[i], left, right) == -1)
		{
			printf("Culo 3 - %d\n", i);
			return (-1);
		}
		if ((left[0] > left[1] || right[1] < right[0]) && left[0] != right[0])
		{
			printf("Culo 4 - %d\n", i);
			return (-1);
		}
		left[0] = left[1];
		right[0] = left[1];
		i++;
	}
	if (next_to(map[0], first_recurrence(map[i], '1'),
		last_recurrence(map[i], '1'), '1') == 0)
	{
		printf("Culo 5\n");
		return (-1);
	}
	return (0);
}
