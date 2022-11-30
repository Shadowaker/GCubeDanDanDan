/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:15:50 by dridolfo          #+#    #+#             */
/*   Updated: 2022/11/30 16:54:27 by dridolfo         ###   ########.fr       */
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
		return (0);
	return (1);
}

int	go_right(char *line, int i)
{
	while (line[i] != '1' && line[i]++ != '\0')
		i++;
	if (line[i] == '\0')
		return (0);
}

int	go_up(char **map, int x, int y)
{
	if (go_left(map[y], x))
		return (1);
	if (go_right(map[y], x))
		return (1);
	if (go_up(map, x, y))
		return (1);
	return (0);
}

int	go_down(char **map, int x, int y)
{
	if (go_left(map[y], x))
		return (1);
	if (go_right(map[y], x))
		return (1);
	if (go_up(map, x, y))
		return (1);
	return (0);
}

int	fill_algorithm(char **map)
{
	int	pl[2];

	find_char(map, 'N', pl);
	if (go_up(map, pl[0], pl[1]))
		return (1);
	if (go_down(map, pl[0], pl[1]))
		return (1);
	return (0);
}


int	map_validator(char **map)
{
	;
}
