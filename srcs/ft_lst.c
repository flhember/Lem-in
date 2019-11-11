/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:59:03 by flhember          #+#    #+#             */
/*   Updated: 2019/11/11 14:53:11 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		print_lst(t_stock *lst)
{
	t_stock	*current;

	current = lst;
	//printf("test = %s\n", lst->first->name);
	while (current != NULL)
	{
		printf("[ %s, x = %d, y = %d ] -> ", current->room, current->x, current->y);
		current = current->next;
	}
	printf("NULL ");
}

void		add_link_empty(t_stock *new, t_stock *lst)
{
	lst = new;
	lst->next = NULL;
	if (lst == NULL)
		printf("wtf\n");
}

void		add_link_last(t_stock *new, t_stock *lst)
{
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}

int			creat_maillon(t_stock *lst, char *name, char *x, char *y, int flag)
{
	t_stock	*new;
	flag = 0;
	new = NULL;
	if (!(new = (t_stock*)ft_memalloc(sizeof(t_stock))))
		return (-1);
	new->room = ft_strdup(name);
	new->x = ft_atoi(x);
	new->y = ft_atoi(y);
	new->next = NULL;
	//flag == 1 ? new->start = 1 : new->start;
	//flag == 2 ? new->end = 1 : new->start;
	if (lst == NULL)// && lst->last == NULL)
	{
		printf("toto\n");
		add_link_empty(new, lst);
	}
	else
	{
		add_link_last(new, lst);
	}
//	printf("lst->name = [%s]\n", *lst.room);
	return (1);
}
