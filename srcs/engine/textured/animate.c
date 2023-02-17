/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:43:26 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/17 12:18:21 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"

static void	next_fp(t_game *game, t_object *obj)
{
	if (game->a_phase == 0)
		obj->tex = &(game->texts->fireplaces->fp0);
	else if (game->a_phase == 1)
		obj->tex = &(game->texts->fireplaces->fp1);
	else if (game->a_phase == 2)
		obj->tex = &(game->texts->fireplaces->fp2);
	else if (game->a_phase == 3)
		obj->tex = &(game->texts->fireplaces->fp3);
}

void	update_animation(t_game *game)
{
	static int	i = 0;
	t_object	*obj;

	if (i == 3)
	{
		i = 0;
		obj = game->objs;
		while (obj)
		{
			if (ft_isinstr("F", obj->type))
				next_fp(game, obj);
			obj = obj->next;
		}
		if (game->a_phase == 3)
			game->a_phase = 0;
		else
			game->a_phase += 1;
	}
	else
		i++;
}
