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

t_object	*newObject(t_game *game, double dist, t_tex *tex)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->x = -1;
	new->y = -1;
	new->type = '\0';
	new->dist = dist;
	new->tex = tex;
	new->next = NULL;
	return (new);
}

t_object	*add_front_object(t_game *game, t_object **objs, double dist,
	t_tex *tex)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->x = game->player->pos[0];
	new->y = game->player->pos[1];
	new->dist = dist;
	new->next = *objs;
	new->tex = tex;
	*objs = new;
	return (new);
}
/*
t_object *add_sorted_object(t_object **sorted, t_object *obj)
{
	t_object	*first;
	t_object	*previous;

	if (!*sorted)
		return ((*sorted = obj));
	first = *sorted;
	previous = NULL;
	while (*sorted && obj->dist < (*sorted)->dist)
	{
		previous = *sorted;
		*sorted = (*sorted)->sorted;
	}
	if (!previous)
	{
		obj->sorted = *sorted;
		*sorted = obj;
	}
	else
	{
		obj->sorted = previous->sorted;
		previous->sorted = obj;
		*sorted = first;
	}
	return (obj);
}

t_object	*sort_objects(t_game *game, t_object *objs)
{
	int			pos[2];
	t_object	*sorted;

	sorted = NULL;

	pos[0] = game->player->cam_plane[0];
	pos[1] = game->player->cam_plane[1];
	while (objs)
	{
		objs->dist =
			fabs(((pos[0] - objs->x) * (pos[0] - objs->x)
				+ (pos[1] - objs->y) * (pos[1] - objs->y)));
		objs->sorted = NULL;
		add_sorted_object(&sorted, objs);
		objs = objs->next;
	}
	return (sorted);
}
*/

void	clear_objs(t_object **objs)
{
	t_object	*tmp;

	while (*objs)
	{
		tmp = (*objs)->next;
		free(*objs);
		*objs = tmp;
	}
	*objs = NULL;
}

t_tex	*getTex(t_game *game, char c)
{
	if (c == 'C' || c == 'P')
		return (&game->sprites->column);
	else if (c == 'B')
		return (&game->sprites->barrel);
	else
		return (&game->sprites->barrel);
}

void	getAllObjects(t_game *game)
{
	int			x;
	int			y;
	double		d;
	t_object	*objs;

	y = 0;
	objs = newObject(game, 0, NULL);
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			if (ft_isinstr(OBJS, game->map[y][x]))
			{
				d = sqrtf(powf(y - game->player->pos[1], 2.) + powf(x - game->player->pos[0], 2.));
				objs = add_front_object(game, &objs, d, getTex(game, game->map[y][x]));
				objs->x = x;
				objs->y = y;
				objs->type = game->map[y][x];
			}
			x++;
		}
		y++;
	}
	game->objs = objs;
}
