/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_adja_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:25:07 by flhember          #+#    #+#             */
/*   Updated: 2019/11/14 12:29:30 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_adja(t_lst **lst, t_data *env)
{
	int		i;

	i = 0;
	while (i < env->nb_room)
	{
		printf("----tab[%d]----\n", i);
		if ((*lst)->tab[i]->start == 1)
			printf("\tSTART\n");
		if ((*lst)->tab[i]->end == 1)
			printf("\tEND\n");
		printf("name %s\n", (*lst)->tab[i]->name);
		printf("x %d\n", (*lst)->tab[i]->x);
		printf("y %d\n\n", (*lst)->tab[i]->y);
		i++;
	}
}

void		fill_tab_room(t_stock **room_ptr, t_lst **lst, int i)
{
	int		j;
	t_stock	*room;

	j = 0;
	room = *room_ptr;
	while (j < i)
	{
		room = room->next;
		j++;
	}
	(void)lst;
	(*lst)->tab[i]->name = ft_strdup(room->room);
	printf("test %s -> [%d] s ->[%d] e-> [%d]\n", (*lst)->tab[i]->name, i, room->start, room->end);
	(*lst)->tab[i]->x = room->x;
	(*lst)->tab[i]->y = room->y;
	(*lst)->tab[i]->start = room->start;
	(*lst)->tab[i]->end = room->end;
}

t_lst		*creat_adja_lst(t_stock **room, t_data *env)
{
	int		i;
	t_lst	*lst;

	i = 0;
	lst = NULL;
	printf("nb room = %d\n", env->nb_room);
	if (!(lst = (t_lst*)ft_memalloc(sizeof(t_lst))))
		return (NULL);
	if (!(lst->tab = ft_memalloc(sizeof(t_room) * (env->nb_room + 1))))
		return (NULL);
	while (i < env->nb_room)
	{
		if (!(lst->tab[i] = ft_memalloc(sizeof(t_room) * 1)))
			return (NULL);
		i++;
	}
	i = 0;
	while (i < env->nb_room)
	{
		fill_tab_room(room, &lst, i);
		i++;
	}
//	print_adja(&lst, env);
	return (lst);
}
