/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:15:50 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/13 17:54:55 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

static int	body(char **map, int x, int y)
{
	int	res;

	res = 0;
	if (map[y][x] != '-' && map[y][x] != '1')
	{
		if (map[y][x + 1] == '\0' || map[y + 1] == NULL || x - 1 < 0 || y - 1 < 0)
			res = 1;
		else
		{
			map[y][x] = '-';
			if (map[y][x + 1] != '1')
				res = body(map, x + 1, y);
			if (map[y][x - 1] != '1' && res != 1)
				res = body(map, x - 1, y);
			if (map[y + 1][x] != '1' && res != 1)
				res = body(map, x, y + 1);
			if (map[y - 1][x] != '1' && res != 1)
				res = body(map, x, y - 1);
		}
	}
	return (res);
}

static int	flood_algorithm(char **map)
{
	int	pl[2];

	find_char(map, 'N', pl);
	return (body(map, pl[0], pl[1]));
}

/* Check if the passed array of arrays (MAP) is valid
	and if there is no strange behavior.
RETURNS: 0 on success, != 0 on fail. */
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
			if (!ft_isinstr("NWES0 DCPBG1\n", map[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	map2 = malloc(sizeof(char *) * (ft_matlen(map) + 1));
	ft_cpmat(map, map2, 0);
	res = flood_algorithm(map2);
	free_mat(map2);
	return (res);
}
