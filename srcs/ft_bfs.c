/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:32:43 by flhember          #+#    #+#             */
/*   Updated: 2019/12/03 17:10:40 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static int	add_file(t_lst **lst, t_file **file, int val, int dis)
{
	t_file	*new;
	t_file	*tmp;

	new = NULL;
	tmp = *file;
	(*lst)->tab[val]->status = 1;
	if (!(new = (t_file*)ft_memalloc(sizeof(t_file))))
		return (-1);
	new->value = val;
	new->dist = dis;
	new->next = NULL;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

int			fill_file(t_file **file, t_lst **lst, int i)
{
	t_room *tmp;
	int o;

	o = 0;
	tmp = (*lst)->tab[i];
	while (tmp)
	{
		if (tmp->pos != i)
		{
			if ((*lst)->tab[tmp->pos]->status == 2 || (*lst)->tab[tmp->pos]->status == 1)
				o = 1;
			else if ((add_file(lst, file, tmp->pos, (*lst)->tab[i]->dist + 1)) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void		del_first_file(t_file **file)
{
	t_file	*tmp;

	tmp = *file;
	*file = (*file)->next;
	free(tmp);
}

void		bfs(t_file **file, t_lst **lst)
{
	t_file	*tmp;

	tmp = *file;
	while (tmp)
	{
		(*lst)->tab[tmp->value]->dist = tmp->dist;
//		printf("termine %s\n", (*lst)->tab[tmp->value]->name);
//		printf("vql = %d\n", tmp->value);
		fill_file(file, lst, tmp->value);
		(*lst)->tab[tmp->value]->status = 2;
//		del_first_file(file);
		tmp = tmp->next;
	}
//	printf("ca sort\n");
}
