/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:24:07 by dridolfo          #+#    #+#             */
/*   Updated: 2022/12/03 17:30:25 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

/*
RETURNS: the absolute value of a double (I) */
double	absf(double i)
{
	if (i < 0)
		return (i * -1.0);
	else
		return (i);
}
