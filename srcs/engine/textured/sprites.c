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

t_object	*add_front_object(t_game *game, t_object **objs, double dist,
	t_tex *tex)
{
	t_object	*new;

	if (!(new = (t_object*)malloc(sizeof(*new))))
		return (NULL);
	new->x = game->player->pos[0];
	new->y = game->player->pos[1];
	new->dist = dist;
	new->next = *objs;
	new->tex = tex;
	*objs = new;
	return (new);
}

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
		add_sorted_obj(&sorted, objs);
		objs = objs->next;
	}
	return (sorted);
}

void	delete_obj(t_object **objs, int x, int y)
{
	t_object	*tmp;
	t_object	*previous;
	t_object	*first;

	first = *objs;
	previous = NULL;
	while (*objs)
	{
		if ((*objs)->x == x && (*objs)->y == y)
		{
			tmp = *objs;
			if (!previous)
				*objs = tmp->next;
			else
				previous->next = tmp->next;
			free(tmp);
			if (previous)
				*objs = first;
			return ;
		}
		previous = *objs;
		*objs = (*objs)->next;
	}
	*objs = first;
}

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

int	getObjects(t_game *game)
{
	t_object		*sorted;
	double			inv_det;
	t_sprite_draw	spr;

	inv_det = 1. / ((game->player->cam_plane[0] * game->player->dir[1]) - (game->player->cam_plane[1] * game->player->dir[0]));
	sorted = sort_sprites(game, game->sprites);
	while (sorted)
	{
		if (sorted->dist > .1)
		{
			;
		}
		sorted = sorted->sorted;
	}
}
