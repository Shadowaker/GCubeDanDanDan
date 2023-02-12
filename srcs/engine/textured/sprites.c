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
	else
		return (&game->texts->door);
}

void	getAllObjects(t_game *game)
{
	int			x;
	int			y;
	double		d;
	t_object	*objs;

	y = 0;
	objs = NULL;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			if (ft_isinstr(OBJS, game->map[y][x]))
			{
				d = INT16_MAX;
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

void	draw_sprites(t_game *game, double *zbuff)
{
	t_object	*obj;

	obj = game->sorted;
	while (obj)
	{
		if (obj->dist > .1)
		{
			double	spr_x = (obj->x + 0.5) - game->player->pos[0];
			double	spr_y = (obj->y + 0.5) - game->player->pos[1];

			double	inv_det = 1.0 / (game->player->cam_plane[0] * game->player->dir[1] - game->player->dir[0] * game->player->cam_plane[1]);

			double	transfX = inv_det * (game->player->dir[1] * spr_x - game->player->dir[0] * spr_y);
			double	transfY = inv_det * (-game->player->cam_plane[1] * spr_x + game->player->cam_plane[0] * spr_y);

			int	spr_screen_x = (((double)(WINDOW_W) / 2.) * (1. + transfX / transfY));
			int	vmovesreen = VMOVE / transfY;
			int	spr_h = fabs(WINDOW_H / transfY);

			int	drawY[2];
			int	drawX[2];

			drawY[0] = -spr_h / 2 + WINDOW_H / 2 + vmovesreen;
			if (drawY[0] < 0)
				drawY[0] = 0;
			drawY[1] = spr_h / 2 + WINDOW_H / 2 + vmovesreen;
			if (drawY[1] >= WINDOW_H)
				drawY[1] = WINDOW_H - 1;

			int spr_w = fabs((WINDOW_H / transfY));
			drawX[0] = - spr_w / 2 + spr_screen_x;
			if (drawX[0] < 0)
				drawX[0] = 0;
			drawX[1] = spr_w / 2 + spr_screen_x;
			if (drawX[1] >= WINDOW_W)
				drawX[1] = WINDOW_W - 1;

			int	stripe = drawX[0];
			while (stripe < drawX[1])
			{
				int	texX = (256 * (stripe - (-spr_w / 2 + spr_screen_x)) * obj->tex->w / spr_w) / 256;
				if (transfY > 0 && transfY < zbuff[stripe])
				{
					int	v = drawY[0];
					while (v < drawY[1])
					{
						int d = (v - vmovesreen) * 256 - WINDOW_H * 128 + spr_h * 128;
						int texY = ((d * obj->tex->h) / spr_h) / 256;
						unsigned int color = get_pixel(&obj->tex->xpm, texX, texY);
						if (transfY > 5.0 && color & 0x0FFFFFFF)
							my_mlx_pixel_put(game->img, stripe, v, color * (0.0) + create_rgb(game->f[0], game->f[1], game->f[2]));
						else if (transfY > 4.9 && color & 0x0FFFFFFF)
							my_mlx_pixel_put(game->img, stripe, v, color * (1 - 0.75) + 0.75 * create_rgb(game->f[0], game->f[1], game->f[2]));
						else if (transfY > 4.8 && color & 0x0FFFFFFF)
							my_mlx_pixel_put(game->img, stripe, v, color * (1 - 0.50) + 0.50 * create_rgb(game->f[0], game->f[1], game->f[2]));
						else if (transfY > 4.6 && color & 0x0FFFFFFF)
							my_mlx_pixel_put(game->img, stripe, v, color * (1 - 0.25) + 0.25 * create_rgb(game->f[0], game->f[1], game->f[2]));
						else if (color & 0x0FFFFFFF)
							my_mlx_pixel_put(game->img, stripe, v, color);
						//if (color & 0x0FFFFFFF)
						//	my_mlx_pixel_put(game->img, stripe, v, color);
						v++;
					}
				}
				stripe++;
			}
		}
		obj = obj->sort;
	}
}
