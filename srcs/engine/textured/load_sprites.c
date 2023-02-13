/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:57:30 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/13 18:00:38 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"

int	load_sprites(t_game *game, t_textures *texts)
{
	if (load_text(game, &(game->texts->barrel), BARREL))
		return (1);
	if (load_text(game, &(game->texts->column), PILLAR))
		return (1);
	if (load_text(game, &(game->texts->greenlight), GREENLIGHT))
		return (1);
	return (0);
}

