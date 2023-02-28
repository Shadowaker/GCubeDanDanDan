/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:54:35 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/28 15:06:54 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

void	ft_lstprint(t_object *lst)
{
	static int	i = 0;

	while (lst)
	{
		printf("%p\n", lst);
		printf("node: %d - x: %d - y: %d - ", i, lst->x, lst->y);
		printf("dist: %f - type: %c - next: %p\n", lst->dist,
			lst->type, lst->next);
		lst = lst->next;
	}
}

void	ft_sortprint(t_object *lst)
{
	static int	i = 0;
	t_object	*sort;

	while (lst)
	{
		sort = lst->sort;
		lst = lst->next;
		if (!sort)
			continue ;
		else
		{
			printf("%p\n", sort);
			printf("node: %d - x: %d - y: %d - ", i, sort->x, sort->y);
			printf("dist: %f - type: %c - next: %p\n", sort->dist,
				sort->type, sort->next);
		}
	}
}
