/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_stock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:17:24 by flhember          #+#    #+#             */
/*   Updated: 2019/11/11 12:44:53 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_stock		*creat_maillon_stock(void)
{
	t_stock		*new;

	new = NULL;
	if (!(new = (t_stock*)ft_memalloc(sizeof(t_stock))))
		return (NULL);
	new->name = NULL;
	return (new);
}

void		add_maillon_end(t_stock *room, t_stock *new)
	while (room->next != NULL)
		room = room->next;
	room->next = new;
	new->next = NULL;
	return (0);
}

void		free_lst_stock(t_stock *room)
{
	t_stock		*tmp;

	tmp = NULL;
	while (room)
	{
		tmp = room->next;
		free(*room);
		room = tmp;
	}
}
