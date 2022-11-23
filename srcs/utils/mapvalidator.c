/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:15:50 by dridolfo          #+#    #+#             */
/*   Updated: 2022/11/23 19:59:10 by dridolfo         ###   ########.fr       */
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
	*left = first_recurrence(str, '1');
	if (*left == -1)
		return (1);
	while (str[*left] != '\0' && str[*left] == '1')
		(*left)++;
	*right = last_recurrence(str, '1');
	if (*right == -1)
		return (1);
	while (*right >= *left && str[*right] == '1')
		(*right)--;
	printf("left: %d	right: %d\n", *left, *right);
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
	int	left;
	int	right;
	int	max;

	i = 1;
	max = ft_matlen(map) - 1;
	if (first_to_last(map[0], &left, &right) == -1)
		return (-1);
	if (next_to(map[0], first_recurrence(map[i], '1'),
		last_recurrence(map[i], '1'), '1') == 0)
		return (-1);
	while (i < max)
	{
		if (first_to_last(map[i], &left, &right) == -1)
			return (-1);
		if (map[i - 1][left] != '1' || map[i - 1][right] != '1')
		{
			printf("Culo 4 - %d\n", i);
			return (-1);
		}
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
