/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_best_road.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:59:57 by flhember          #+#    #+#             */
/*   Updated: 2019/12/07 17:39:43 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static int	pars_pipe_best(t_lst **lst, t_room *tmp, int i, int j)
{
	tmp = (*lst)->tab[j];
	while (tmp)
	{
		if (tmp->pos == (*lst)->tab[i]->pos)
		{
			(*lst)->nb_best_move++;
			if ((*lst)->tab[j]->start == 0 && (*lst)->tab[j]->end == 0)
				(*lst)->tab[j]->road = (*lst)->nb_road;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	best_road_bis(t_lst **lst, int ds, int i, int j)
{
	int		end;

	end = i;
	while (ds >= 0)
	{
		printf("\nb %s -> %d ", (*lst)->tab[i]->name, ds);
		ds--;
		j = 0;
		while (j < (*lst)->nb_room)
		{
			if ((*lst)->tab[j]->dist == ds && (*lst)->tab[j]->road == 0)
			{
				if ((pars_pipe_best(lst, NULL, i, j)))
				{
					i = j;
					j = (*lst)->nb_room + 2;
				}
			}
			j++;
			if (j == (*lst)->nb_room && ds == (*lst)->tab[end]->dist - 1)
				return (-1);
		}
	}
	return (0);
}

int			best_road(t_lst **lst, t_data *env)
{
	int		i;
	int		ds;

	ds = 0;
	i = env->end;
	if (bfs(env, lst) == -1)
		return (-1);
	ds = (*lst)->tab[i]->dist;
	(*lst)->nb_road++;
	if ((best_road_bis(lst, ds, i, 0)) == -1)
		return (-1);
	return (0);
}
