/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:15:50 by dridolfo          #+#    #+#             */
/*   Updated: 2022/12/02 16:24:17 by dridolfo         ###   ########.fr       */
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

static int	body(char **map, int x, int y)
{
	int	res;

	printf("////////////////////////////////////////////////////////////////\n");
	print_mat(map, '~');
	printf("////////////////////////////////////////////////////////////////\n");
	res = 0;
	if (map[y][x] != '-')
	{
		if (map[y][x] == '1')
			res = 0;
		else if (map[y][x + 1] == '\0')
			res = 1;
		else
		{
			map[y][x] = '-';
			res = body(map, x + 1, y);
		}
	}
	if (map[y][x] != '-')
	{
		if (map[y][x] == '1')
			res = 0;
		else if (x - 1 < 0)
			res = 1;
		else
		{
			map[y][x] = '-';
			res = body(map, x - 1, y);
		}
	}
	if (map[y][x] != '-')
	{
		if (map[y][x] == '1')
			res = 0;
		else if (map[y + 1] == NULL)
			res = 1;
		else
		{
			map[y][x] = '-';
			res = body(map, x, y + 1);
		}
	}
	if (map[y][x] != '-')
	{
		if (map[y][x] == '1')
			res = 0;
		else if (y - 1 < 0)
			res = 1;
		else
		{
			map[y][x] = '-';
			res = body(map, x, y - 1);
		}
	}
	return (res);
}

int	flood_algorithm(char **map)
{
	int	pl[2];

	find_char(map, 'N', pl);
	if (pl[0] == -1 || pl[1] == -1)
		return (1);
	return (body(map, pl[0], pl[1]));
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
	int		i;
	int		j;
	int		res;
	char	**map2;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (!ft_isinstr("NWES0 DB1\n", map[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	map2 = malloc(sizeof(char *) * (ft_matlen(map) + 1));
	ft_cpmat(map, map2, 0);
	printf("////////////////////////////////////////////////////////////////\n\t\tMAP 2\n");
	print_mat(map2, '@');
	printf("////////////////////////////////////////////////////////////////\n");
	res = flood_algorithm(map2);
	free_mat(map2);
	printf("\n%d \n", res);
	return (res);
}
