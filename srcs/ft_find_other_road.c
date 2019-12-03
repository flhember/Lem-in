/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_other_road.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:52:59 by flhember          #+#    #+#             */
/*   Updated: 2019/12/03 16:10:03 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int			pars_pipe_end(t_lst **lst, t_room *tmp, int i, size_t j)
{
	while (tmp)
	{
		if (tmp->pos == (*lst)->tab[i]->pos && (*lst)->tab[j]->road == 0)
		{
			(*lst)->tab[j]->road = (*lst)->nb_road;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int		other_road_bis(t_data *env, t_lst **lst, int ds, int i, size_t j, t_room *tmp)
{
	while ((*lst)->tab[i]->end == 0)
	{
		printf("\no. %s -> %d ", (*lst)->tab[i]->name, ds);
		ds++;
		j = 0;
		while (j < env->nb_room)
		{
			if ((*lst)->tab[j]->dist == ds && (*lst)->tab[j]->road == 0)
			{
				tmp = (*lst)->tab[j];
				if ((pars_pipe_end(lst, tmp, i, j)) )
				{
					i = j;
					j = env->nb_room + 2;
				}
			}
			j++;
			if (j == env->nb_room)
			{
				ds -= 2;
				if (ds == -1)
					return (-1);
			}
		}
	}
	return (0);
}

int			other_road(t_lst **lst, t_data *env)
{
	int		i;
	int		ds;

	i = env->start;
	ds = (*lst)->tab[i]->dist;
	while ((*lst)->nb_road < env->nb_pos)
	{
		(*lst)->nb_road++;
		if ((other_road_bis(env, lst, ds, i, 0, NULL)) == -1)
			return (-1);
	}
	return (0);
}
