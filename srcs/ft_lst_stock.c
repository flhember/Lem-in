/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_stock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:31:10 by flhember          #+#    #+#             */
/*   Updated: 2019/11/15 19:27:17 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		print_lst(t_stock **lst)
{
	t_stock	*tmp;

	tmp = *lst;
	while (tmp->next)
	{
		printf("[ %s, x = %d, y = %d pipe = %d] -> ", tmp->room, tmp->x, tmp->y, tmp->pipe);
		tmp = tmp->next;
	}
	printf("NULL ");
}

void		add_link_last(t_stock *new, t_stock **lst)
{
	new->next = *lst;
	*lst = new;
}

int			creat_maillon(t_stock **lst, char *name, char *x, char *y)
{
	t_stock	*new;

	new = NULL;
	if (!(new = (t_stock*)ft_memalloc(sizeof(t_stock))))
		return (-1);
	if (!(new->room = ft_strdup(name)))
		return (-1);
	new->x = ft_atoi(x);
	new->y = ft_atoi(y);
	new->next = NULL;
	add_link_last(new, lst);
	return (1);
}
