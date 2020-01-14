/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_best_road.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:02:43 by flhember          #+#    #+#             */
/*   Updated: 2020/01/07 14:14:21 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int			pars_pipe(t_lst **lst, t_room *tmp, int i, size_t j)
{
	while (tmp)
	{
		if (tmp->pos == (*lst)->tab[i]->pos)
		{
			if ((*lst)->tab[j]->start == 0)
			{
				(*lst)->tab[j]->road = (*lst)->nb_road;
				(*lst)->nb_best_move++;
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int		best_road_bis(t_data *env, t_lst **lst, int ds, int i, size_t j, t_room *tmp)
{
	while (ds >= 0)
	{
		ds--;
		j = 0;
		while (j < env->nb_room)
		{
			if ((*lst)->tab[j]->dist == ds && (*lst)->tab[j]->road == 0)
			{
				tmp = (*lst)->tab[j];
				if ((pars_pipe(lst, tmp, i, j)))
				{
					i = j;
					j = env->nb_room + 2;
				}
			}
			j++;
			if (j == env->nb_room && ds == (*lst)->tab[env->end]->dist - 1)
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
	if (bfs_best(env, lst) == -1)
		return (-1);
	ds = (*lst)->tab[i]->dist;
	(*lst)->nb_road++;
	if ((best_road_bis(env, lst, ds, i, 0, NULL)) == -1)
		return (-1);
//	print_adja(lst, env);
	(*lst)->nb_road++;
	return (0);
}
