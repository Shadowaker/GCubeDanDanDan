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

int	draw_sprites(t_game *game)
{
	t_object	*obj;

	obj = game->objs;
	while (obj)
	{
		double	spr_x = obj->sort->x - game->player->pos[0];
		double	spr_y = obj->sort->y - game->player->pos[1];

		double	inv_det = 1.0 / (game->player->cam_plane[0] * game->player->dir[1] - game->player->dir[0] * game->player->cam_plane[1]);

		double	transfX = inv_det * (game->player->dir[1] * spr_x - game->player->dir[0] * spr_y);
		double	transfY = inv_det * (-game->player->dir[1] * spr_x - game->player->dir[0] * spr_y);

		int	spr_screen_x = (WINDOW_W / 2) * (1 + transfX / transfY);
		int	spr_screen_y = abs(WINDOW_H / transfY);

		int	drawY[2];
		int	drawX[2];

		drawY[0] = -spr_screen_y / 2 + WINDOW_H / 2;
		if (drawY[0] < 0)
			drawY[0] = 0;
		drawY[1] = spr_screen_y / 2 + WINDOW_H / 2;
		if (drawY[1] >= WINDOW_H)
			drawY[1] = WINDOW_H - 1;

		int spr_w = abs((WINDOW_H / transfY));
		int	drawX[0] = - spr_w / 2 + spr_screen_x;
		if (drawX[0] < 0)
			drawX[0] = 0;
		int	draw[1] =;



	}

	for(int i = 0; i < numSprites; i++)
    {

      //calculate width of the sprite
      int spriteWidth = abs( int (h / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= w) drawEndX = w - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * texHeight) / spriteHeight) / 256;
          Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
          if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible colo
}
