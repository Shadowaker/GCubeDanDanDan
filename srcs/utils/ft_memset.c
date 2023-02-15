/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:30:44 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/15 15:20:55 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

/* Set the memory of a void * (B) in a int (C).
RETURNS: The original pointer B passed. */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*buf;

	buf = (unsigned char *) b;
	while (len-- > 0)
		*(buf++) = (unsigned char) c;
	return (b);
}
