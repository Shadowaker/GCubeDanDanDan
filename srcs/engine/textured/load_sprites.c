/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:57:30 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/01 11:11:58 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/gcube.h"

int	load_sprites(t_game *game, t_sprites *sprites)
{
	if (load_text(game, &(sprites->barrel), BARREL))
		return (1);
	if (load_text(game, &(sprites->column), PILLAR))
		return (1);
	return (0);
}

