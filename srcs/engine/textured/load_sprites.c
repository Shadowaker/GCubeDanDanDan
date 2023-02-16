/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:57:30 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/16 13:28:38 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"

static int	load_fireplace(t_game *game, t_textures *texts, t_fireplace *fireplace)
{
	if (load_text(game, &(game->texts->fireplace->fp0), FP1))
		return (1);
	if (load_text(game, &(game->texts->fireplace->fp1), FP2))
		return (1);
	if (load_text(game, &(game->texts->fireplace->fp2), FP3))
		return (1);
	if (load_text(game, &(game->texts->fireplace->fp3), FP4))
		return (1);
	return (0);
}

int	load_sprites(t_game *game, t_textures *texts, t_fireplace *fireplace)
{
	if (load_text(game, &(game->texts->barrel), BARREL))
		return (1);
	if (load_text(game, &(game->texts->column), PILLAR))
		return (1);
	if (load_text(game, &(game->texts->greenlight), GREENLIGHT))
		return (1);
	if (load_fireplace(game, texts, fireplace))
		return (1);
	return (0);
}
