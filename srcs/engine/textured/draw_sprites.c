/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:09:26 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/15 16:14:49 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"

static void	draw_spritino(t_game *game, t_dsprite *spr, t_object *obj,
				double *zbuff)
{
	int				v;
	int				stripe;
	int				d;
	int				tex[2];
	unsigned int	color;

	stripe = spr->drawx[0];
	while (stripe < spr->drawx[1])
	{
		tex[0] = (256 * (stripe - (-spr->spr_w / 2 + spr->spr_screen_x))
				* obj->tex->w / spr->spr_w) / 256;
		if (spr->transf[1] > 0 && spr->transf[1] < zbuff[stripe])
		{
			v = spr->drawy[0] - 1;
			while (++v < spr->drawy[1])
			{
				d = (v) * 256 - WINDOW_H * 128 + spr->spr_h * 128;
				tex[1] = ((d * obj->tex->h) / spr->spr_h) / 256;
				color = get_pixel(&obj->tex->xpm, tex[0], tex[1]);
				if (color & 0x0FFFFFFF)
					my_mlx_pixel_put(game->img, stripe, v, color);
			}
		}
		stripe++;
	}
}

static void	draw_spritone(t_game *game, t_dsprite *spr, t_object *obj)
{
	spr->spr_h = fabs(WINDOW_H / spr->transf[1]);
	spr->drawy[0] = -spr->spr_h / 2 + WINDOW_H / 2;
	if (spr->drawy[0] < 0)
		spr->drawy[0] = 0;
	spr->drawy[1] = spr->spr_h / 2 + WINDOW_H / 2;
	if (spr->drawy[1] >= WINDOW_H)
		spr->drawy[1] = WINDOW_H - 1;
	spr->spr_w = fabs((WINDOW_H / spr->transf[1]));
	spr->drawx[0] = -spr->spr_w / 2 + spr->spr_screen_x;
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
			spr.inv_det = 1.0 / (game->player->cam_plane[0]
					* game->player->dir[1]
					- game->player->dir[0] * game->player->cam_plane[1]);
			spr.transf[0] = spr.inv_det * (game->player->dir[1] * spr.pos[0]
					- game->player->dir[0] * spr.pos[1]);
			spr.transf[1] = spr.inv_det * (-game->player->cam_plane[1]
					* spr.pos[0]
					+ game->player->cam_plane[0] * spr.pos[1]);
			spr.spr_screen_x = (((double)(WINDOW_W) / 2.) * (1.
						+ spr.transf[0] / spr.transf[1]));
			draw_spritone(game, &spr, obj);
			draw_spritino(game, &spr, obj, zbuff);
		}
		obj = obj->sort;
	}
}
