/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:15:50 by dridolfo          #+#    #+#             */
/*   Updated: 2022/11/21 09:51:03 by dridolfo         ###   ########.fr       */
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
	int	left;
	int	right;
	int	max;

	i = 1;
	max = ft_matlen(map) - 1;
	if (first_to_last(map[0], &left, &right) == -1)
		return (1);
	while (i < max)
	{
		if (first_to_last(map[i], &left, &right) == -1)
			return (1);
		if (map[i - 1][left] != '1' || map[i - 1][right] != '1')
			return (1);
		i++;
	}
	if (map[i][left] != '1' || map[i][right] != '1');
	return (0);
}
