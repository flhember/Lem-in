/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_road.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:10:53 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/10 16:40:49 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		link_fail(t_data *env, int i, int j)
{
	t_fail *road;
	t_fail *tmp;

	tmp = env->road[i]->f_road;
	if (!(road = ft_memalloc(sizeof(t_fail))))
		return (-1);
	road->id = j;
	road->next = NULL;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = road;
	return (1);
}

void	mark_fail(t_data *env, int i, int j)
{
	if (env->road[i]->f_road == NULL)
	{
		if (!(env->road[i]->f_road = ft_memalloc(sizeof(t_fail))))
			return ;
		env->road[i]->f_road->id = j;
	}
	else
		link_fail(env, i, j);
	if (env->road[j]->f_road == NULL)
	{
		if (!(env->road[j]->f_road = ft_memalloc(sizeof(t_fail))))
			return ;
		env->road[j]->f_road->id = i;
	}
	else
		link_fail(env, j, i);
	env->road[i]->state = -1;
	env->road[j]->state = -1;
	env->road[i]->col++;
	env->road[j]->col++;
}

int		find_id(t_data *env, int i, int j)
{
	t_fail *tmp;

	tmp = env->road[i]->f_road;
	while (tmp)
	{
		if (tmp->id == j)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	solve_cross(t_data *env, int i, int j, t_road *nex)
{
	t_road *act;

	while (i < env->nb_road_f - 1)
	{
		act = env->road[i]->next;
		while (act->next)
		{
			while (j < env->nb_road_f)
			{
				nex = env->road[j]->next;
				while (nex->next && find_id(env, i, j) == 0)
				{
					if (act->index == nex->index && find_id(env, i, j) == 0)
						mark_fail(env, i, j);
					else
						nex = nex->next;
				}
				j++;
			}
			act = act->next;
			j = i + 1;
		}
		i++;
		j = i + 1;
	}
}

int		sort_road(t_data *env, int i)
{
	t_road	*tmp;

	tmp = NULL;
	env->nb_road_f--;
	if (env->nb_road_f == 1)
		return (1);
	while (i < env->nb_road_f - 1)
	{
		env->road[i]->state = 0;
		env->road[i]->col = 0;
		if (env->road[i]->size > env->road[i + 1]->size)
		{
			tmp = env->road[i];
			env->road[i] = env->road[i + 1];
			env->road[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	solve_cross(env, 0, 1, NULL);
	choose_road(env);
	return (1);
}
