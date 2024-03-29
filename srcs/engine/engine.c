/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:30:32 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/26 15:03:21 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

void	minimap(t_game *game, t_img *img)
{
	char	**mini;
	int		i;

	i = 0;
	mini = malloc(sizeof(char *) * 11);
	while (i < 11)
		mini[i++] = ft_calloc(1, 11);
	mini[i] = NULL;
}

void	engine(t_game *game, t_img *img, t_ray *ray)
{
	char	**mini;

	if (TEXT)
		raycast_text(game, img, ray);
	else
		raycast(game, img, ray);
	render_minimap(game);
}
