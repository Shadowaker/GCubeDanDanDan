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
		*sorted = (*sorted)->sort;
	}
	if (!previous)
	{
		obj->sort = *sorted;
		*sorted = obj;
	}
	else
	{
		obj->sort = previous->sort;
		previous->sort = obj;
		*sorted = first;
	}
	return (obj);
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

t_tex	*getTex(t_game *game, char c)
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

void	getAllObjects(t_game *game)
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
				objs = add_front_object(game, &objs, d, getTex(game, game->map[y][x]));
				objs->x = x;
				objs->y = y;
				objs->type = game->map[y][x];
			}
		}
	}
	game->objs = objs;
}

t_object	*sortObjects(t_game *game)
{
	int			pos[2];
	t_object	*sorted;
	t_object	*objs;

	sorted = NULL;
	objs = game->objs;
	while (objs)
	{
		objs->dist = powf(objs->y - game->player->pos[1], 2.) + powf(objs->x - game->player->pos[0], 2.);
		objs->sort = NULL;
		add_sorted_object(&sorted, objs);
		objs = objs->next;
	}
	return (sorted);
}

void	draw_spritino(t_game *game, t_dsprite *spr, t_object *obj, double *zbuff)
{
	int	v;
	int	stripe;
	int	d;
	int	tex[2];

	stripe = spr->drawx[0];
	while (stripe < spr->drawx[1])
	{
		tex[0] = (256 * (stripe - (-spr->spr_w / 2 + spr->spr_screen_x)) * obj->tex->w / spr->spr_w) / 256;
		if (spr->transf[1] > 0 && spr->transf[1] < zbuff[stripe])
		{
			v = spr->drawy[0];
			while (v < spr->drawy[1])
			{
				d = (v) * 256 - WINDOW_H * 128 + spr->spr_h * 128;
				tex[1] = ((d * obj->tex->h) / spr->spr_h) / 256;
				unsigned int color = get_pixel(&obj->tex->xpm, tex[0], tex[1]);
				if (color & 0x0FFFFFFF)
					my_mlx_pixel_put(game->img, stripe, v, color);
				v++;
			}
		}
		stripe++;
	}
}

void	draw_spritone(t_game *game, t_dsprite *spr, t_object *obj)
{
	spr->spr_h = fabs(WINDOW_H / spr->transf[1]);
	spr->drawy[0] = -spr->spr_h / 2 + WINDOW_H / 2;
	if (spr->drawy[0] < 0)
		spr->drawy[0] = 0;
	spr->drawy[1] = spr->spr_h / 2 + WINDOW_H / 2;
	if (spr->drawy[1] >= WINDOW_H)
		spr->drawy[1] = WINDOW_H - 1;
	spr->spr_w = fabs((WINDOW_H / spr->transf[1]));
	spr->drawx[0] = - spr->spr_w / 2 + spr->spr_screen_x;
	if (spr->drawx[0] < 0)
		spr->drawx[0] = 0;
	spr->drawx[1] = spr->spr_w / 2 + spr->spr_screen_x;
	if (spr->drawx[1] >= WINDOW_W)
		spr->drawx[1] = WINDOW_W - 1;
}

void	draw_sprites(t_game *game, double *zbuff)
{
	t_object	*obj;
	t_dsprite	spr;

	obj = game->sorted;
	while (obj)
	{
		if (obj->dist > .1)
		{
			spr.pos[0] = (obj->x + 0.5) - game->player->pos[0];
			spr.pos[1] = (obj->y + 0.5) - game->player->pos[1];
			spr.inv_det = 1.0 / (game->player->cam_plane[0] * game->player->dir[1]
						- game->player->dir[0] * game->player->cam_plane[1]);

			spr.transf[0] = spr.inv_det * (game->player->dir[1] * spr.pos[0]
							- game->player->dir[0] * spr.pos[1]);
			spr.transf[1] = spr.inv_det * (-game->player->cam_plane[1] * spr.pos[0]
							+ game->player->cam_plane[0] * spr.pos[1]);
			spr.spr_screen_x = (((double)(WINDOW_W) / 2.) * (1. + spr.transf[0] / spr.transf[1]));
			draw_spritone(game, &spr, obj);
			draw_spritino(game, &spr, obj, zbuff);
		}
		obj = obj->sort;
	}
}
