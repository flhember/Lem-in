/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_rep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:20:19 by flhember          #+#    #+#             */
/*   Updated: 2020/02/04 18:15:27 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int new_nb_road(t_data *env)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->state == 0)
			nb++;
		i++;
	}
	return (nb);
}

void	fill_tab_sol(t_data *env)
{
	int i;
	int j;
	int size;

	i = 0;
	j = 0;
	size = new_nb_road(env);
	if (!(env->road_sol = ft_memalloc(sizeof(int) * size )))
		return ;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->state >= 0)
		{
			env->road_sol[j] = i;
			j++;
		}
		i++;
	}
	env->nb_road_f = size;
}

int		treat_better(t_data *env, int limit)
{
	int i;
	int total;

	total = 0;
	i = 0;
	while (i < limit)
	{
		total = total + ((env->nb_ants / limit) + env->road[i]->size);
		i++;
	}
	total = total / limit;
	return (total);
}

int		ants_treat(t_data *env)
{
	int i;
	int limit;
	int total_cost;
	int tmp;

	i = 0;
	limit = 1;
	env->total_road = 0;
	fill_tab_sol(env);
	total_cost = treat_better(env, limit);
	ft_printf("total_cost = %d | limit = %d | nb_road = %d\n\n", total_cost, limit, env->nb_road_f);
	while (limit < env->nb_road_f)
	{
		limit++;
		tmp = total_cost;
		total_cost = treat_better(env, limit);
	ft_printf("total_cost = %d | limit = %d | nb_road = %d\n", total_cost, limit, env->nb_road_f);
		if (total_cost > tmp)
		{
			i++;
			total_cost = tmp;
		}
	}
	limit -= i;
	i = 0;
	env->total_road = limit;
	env->total_cost = total_cost;
	ft_printf("Chemins a utiliser = \n");
	while (i < env->total_road)
	{
		ft_printf("Chemin [%d] -> %d room\n", i, env->road[i]->size);
		i++;
	}
	ft_printf("Pour %d coups\n", env->total_cost);
	return (1);
}
