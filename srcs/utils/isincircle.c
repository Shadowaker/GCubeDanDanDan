/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isincircle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:03:55 by dridolfo          #+#    #+#             */
/*   Updated: 2022/12/03 17:39:00 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

/* DEPRECATED */
int	isincircle(int cx, int cy, int x, int y)
{
	int	distance;

	distance = sqrt(pow(x - cx, 2) + pow(y - cy, 2));
	if (distance <= PLAYER_R)
	{
		if (PLAYER_R == distance)
			return (2);
		return (1);
	}
	return (0);
}
