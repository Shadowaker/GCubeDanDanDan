/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:15:50 by dridolfo          #+#    #+#             */
/*   Updated: 2022/12/01 12:21:39 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

void	find_char(char **map, char c, int *ids)
{
	ids[1] = 0;
	while (map[ids[1]] != NULL)
	{
		ids[0] = 0;
		while (map[ids[1]][ids[0]] != '\0')
		{
			if (map[ids[1]][ids[0]] == c)
				return ;
			ids[0]++;
		}
		ids[1]++;
	}
	ids[1] = -1;
	ids[0] = -1;
}

int	go_left(char *line, int i)
{
	while (line[i] != '1' && i > -1)
		i--;
	if (i == -1)
		return (1);
	return (0);
}

int	go_right(char *line, int i)
{
	while (line[i] != '1' && line[i]++ != '\0')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	go_up(char **map, int x, int y)
{
	if (go_left(map[y], x))
		return (1);
	if (go_right(map[y], x))
		return (1);
	if (--y > -1)
	{
		if (go_up(map, x, y))
			return (1);
	}
	if (map[y][x] != '1' && y == 0)
		return (1);
	return (0);
}

int	go_down(char **map, int x, int y)
{
	if (go_left(map[y], x))
		return (1);
	if (go_right(map[y], x))
		return (1);
	if (map[++y] != NULL)
	{
		if (go_down(map, x, ++y))
			return (1);
	}
	if (map[y][x] != '1' && map[y] == NULL)
		return (1);
	return (0);
}

int	fill_algorithm(char **map)
{
	int	pl[2];

	find_char(map, 'N', pl);
	if (pl[0] == -1 || pl[1] == -1)
		return (1);
	while (map[pl[1]][pl[0]] != '\0')
	{
		if (go_up(map, pl[0], pl[1]))
			return (1);
		if (go_down(map, pl[0], pl[1]))
			return (1);
		pl[0]++;
	}
	return (0);
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

int	map_validator(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[i++])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_isinstr("NWES0 DB1", map[i][j++]))
				return (1);
		}
	}
	return(fill_algorithm(map));
}
