/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:57:52 by dridolfo          #+#    #+#             */
/*   Updated: 2022/11/25 12:33:52 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

/* Set all memory of the B pointer to 0.
RETURNS: a NULL pointer.*/
void	*ft_bzero(void *b, size_t len)
{
	unsigned char	*p;

	p = (unsigned char *) b;
	while (len-- > 0)
		*(p++) = '\0';
	return (NULL);
}

/* Malloc SIZE times of COUNT bytes and set
all allocated memory to 0.
RETURNS: pointer to the allocated memory.*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = (void *) malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}
