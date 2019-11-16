/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:29:41 by chcoutur          #+#    #+#             */
/*   Updated: 2019/11/16 19:08:04 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

size_t	ft_lstsize(t_stock **room)
{
	t_stock *cpy;
	size_t	i;

	i = 0;
	cpy = *room;
	if (cpy == NULL)
		return (0);
	while (cpy)
	{
		i++;
		cpy = cpy->next;
	}
	return (i);
}
