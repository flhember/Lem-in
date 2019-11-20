/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_adja_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:25:07 by flhember          #+#    #+#             */
/*   Updated: 2019/11/20 16:47:09 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		print_adja(t_lst **lst, t_data *env)
{
	size_t	i;

	i = 0;
	while (i < env->nb_room)
	{
		ft_printf("----tab[%lu]----\n", i);
		ft_printf("pso tab = %d\n", (*lst)->tab[i]->pos);
		if ((*lst)->tab[i]->start == 1)
			ft_printf("\tSTART\n");
		if ((*lst)->tab[i]->end == 1)
			ft_printf("\tEND\n");
		ft_printf("name %s\n", (*lst)->tab[i]->name);
		ft_printf("x %d\n", (*lst)->tab[i]->x);
		ft_printf("y %d\n\n", (*lst)->tab[i]->y);
		i++;
	}
}

static void	fill_tab_room(t_stock **room_ptr, t_lst **lst, size_t i)
{
	size_t	j;
	int		k;
	t_stock	*room;

	j = 0;
	k = -1;
	room = *room_ptr;
	while (j < i && room)
	{
		room = room->next;
		room->pipe == 0 && room->com == 0 ? k++ : k;
		j++;
	}
	ft_printf("room->room = %s\n", room->room);
	ft_printf("\n\n");
	ft_printf("k = [%d] | name = [%s] | x = [%d] | y = [%d]\n", k, room->room, room->x, room->y);
	if (room->pipe == 1 || room->com == 1)
		return ;
	ft_printf("k = [%d]\n", k);
	(*lst)->tab[k]->pos = k;
	(*lst)->tab[k]->name = ft_strdup(room->room);
	(*lst)->tab[k]->x = room->x;
	(*lst)->tab[k]->y = room->y;
	(*lst)->tab[k]->start = room->start;
	(*lst)->tab[k]->end = room->end;

}

t_lst		*creat_adja_lst(t_stock **room, t_data *env)
{
	size_t	i;
	size_t	size_lst;
	t_lst	*lst;
	/*t_stock *cpy;

	cpy = *room;
	i = 0;
	while (cpy)
	{
		if (cpy->next == NULL)
			ft_printf("NULL\n");
		else
			ft_printf("[%s][%lu]\n", cpy->room,  i);
		cpy = cpy->next;
		i++;
	}*/
	i = 0;
	size_lst = ft_lstsize(room);
	lst = NULL;
	if (!(lst = (t_lst*)ft_memalloc(sizeof(t_lst))))
		return (NULL);
	if (!(lst->tab = ft_memalloc(sizeof(t_room) * (env->nb_room))))
		return (NULL);
	while (i < env->nb_room)
	{
		if (!(lst->tab[i] = ft_memalloc(sizeof(t_room))))
			return (NULL);
		i++;
	}
	ft_printf("size lst = [%lu]\n", size_lst);
	ft_printf("size room = [%lu]\n", env->nb_room);
	ft_printf("i  = [%lu]\n", i);
	lst->tab[env->nb_room] = 0;
	i = 0;
	while (i < size_lst - 1)
	{
		fill_tab_room(room, &lst, i);
		i++;
	}

//	print_adja(&lst, env);
	return (lst);
}
