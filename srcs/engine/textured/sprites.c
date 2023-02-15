/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:38:30 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/02 19:56:20 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"

static t_tex	*get_tex(t_game *game, char c)
{
	if (c == 'C' || c == 'P')
		return (&game->texts->column);
	else if (c == 'B')
		return (&game->texts->barrel);
	else if (c == 'G')
		return (&game->texts->greenlight);
	else
		return (&game->texts->door);
}

void	get_all_objects(t_game *game)
{
	int			x;
	int			y;
	double		d;
	t_object	*objs;

	y = -1;
	objs = NULL;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x] != '\0')
		{
			if (ft_isinstr(OBJS, game->map[y][x]))
			{
				d = INT16_MAX;
				objs = add_front_object(game, &objs, d,
						get_tex(game, game->map[y][x]));
				objs->x = x;
				objs->y = y;
				objs->type = game->map[y][x];
			}
		}
	}
	game->objs = objs;
}
