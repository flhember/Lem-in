/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:59:03 by flhember          #+#    #+#             */
/*   Updated: 2019/11/11 12:13:11 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		print_lst(t_mark *lst)
{
	t_room	*current;

	current = lst->first;
	//printf("test = %s\n", lst->first->name);
	while (current != NULL)
	{
		printf("[ %s, x = %d, y = %d ] -> ", current->name, current->x, current->y);
		current = current->next;
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

int			creat_maillon(t_mark *lst, char *name, char *x, char *y, int flag)
{
	t_room	*new;

	new = NULL;
	if (!(new = (t_room*)ft_memalloc(sizeof(t_room))))
		return (-1);
	new->name = ft_strdup(name);
	new->x = ft_atoi(x);
	new->y = ft_atoi(y);
	flag == 1 ? new->start = 1 : new->start;
	flag == 2 ? new->end = 1 : new->start;
	if (lst->first == NULL && lst->last == NULL)
		add_link_empty(new, lst);
	else
		add_link_last(new, lst);
	return (0);
}
