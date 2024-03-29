/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:57:30 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/28 10:35:20 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"

static int	load_fireplace(t_game *game, t_textures *texts)
{
	if (load_text(game, &(game->texts->ani->fp0), FP1))
		return (1);
	if (load_text(game, &(game->texts->ani->fp1), FP2))
		return (1);
	if (load_text(game, &(game->texts->ani->fp2), FP3))
		return (1);
	if (load_text(game, &(game->texts->ani->fp3), FP4))
		return (1);
	return (0);
}

static int	load_deatheater(t_game *game, t_textures *texts)
{
	if (load_text(game, &(game->texts->ani->de0), DE1))
		return (1);
	if (load_text(game, &(game->texts->ani->de1), DE2))
		return (1);
	if (load_text(game, &(game->texts->ani->de2), DE3))
		return (1);
	if (load_text(game, &(game->texts->ani->de3), DE4))
		return (1);
	if (load_text(game, &(game->texts->ani->de4), DE5))
		return (1);
	return (0);
}

int	load_sprites(t_game *game, t_textures *texts)
{
	if (load_text(game, &(game->texts->barrel), BARREL))
		return (1);
	if (load_text(game, &(game->texts->column), PILLAR))
		return (1);
	if (load_text(game, &(game->texts->greenlight), GREENLIGHT))
		return (1);
	if (load_fireplace(game, texts))
		return (1);
	if (load_deatheater(game, texts))
		return (1);
	return (0);
}
