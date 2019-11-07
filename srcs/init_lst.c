/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:04:55 by flhember          #+#    #+#             */
/*   Updated: 2019/11/07 13:32:22 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		printf_lst(t_mark *lst)
{
	t_room	*courrent;

	courrent = lst->first;
	while (courrent != NULL)
	{
		printf("[ %s ] -> ", courrent->next);
		courrent = courrent->next;
	}
	printf("NULL");
}

void		add_link_empty(t_room *new, t_mark *lst)
{
	new->prev = NULL;
	new->next = NULL;
	lst->first = new;
	lst->last = new;
}

void		add_link_first(t_room *new, t_mark *lst)
{
	new->prev = NULL;
	new->next = lst->first;
	lst->first->prev = new;
	lst->first = new;
	lst->size++;
}

void		add_link_last(t_room *new, t_mark *lst)
{
	new->next = NULL;
	new->prev = lst->last;
	lst->last->next = new;
	lst->last = new;
	lst->size++;
}

t_room		*creat_maillon(char *name, int x, int y, int flag)
{
	t_room	*new;

	new = NULL;
	if (!(new = (t_room*)ft_memalloc(sizeof(t_room))))
		return (NULL);
	new->name = name;
	new->x = x;
	new->y = y;
	comment == 1 ? new->start = 1 : new->start;
	comment == 2 ? new->end = 1 : new->start;
	return (new);
}

void		init_lst(t_mark *lst)
{
	lst->first = NULL;
	lst->last = NULL;
	lst->size = 0;
}
