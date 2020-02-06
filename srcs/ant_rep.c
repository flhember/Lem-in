/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_rep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:20:19 by flhember          #+#    #+#             */
/*   Updated: 2020/02/06 12:35:18 by flhember         ###   ########.fr       */
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

int		treat_better(t_data *env, int limit)
{
	int i;
	int total;
	int nb;

	total = 0;
	i = 0;
	nb = 0;
	while (i < limit)
	{
		total = total + ((env->nb_ants / limit) + env->road[env->road_sol[i]]->size);
		env->road[i]->nb_ant = total; // non juste pour test
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
	total_cost = treat_better(env, limit);
	ft_printf("total_cost = %d | limit = %d | nb_road = %d\n\n", total_cost, limit, env->nb_road_f);
	while (limit < env->nb_road_f)
	{
		limit++;
		tmp = total_cost;
		total_cost = treat_better(env, limit);
		ft_printf("total_cost = %d | limit = %d | nb_road = %d\n", total_cost, limit, env->nb_road_f);
		if (total_cost >= tmp)
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
		ft_printf("Chemin [%d] -> %d room\n", env->road_sol[i], env->road[env->road_sol[i]]->size);
		env->road[i]->nb_ant = env->road[env->road_sol[i]]->size;
		i++;
	}
	ft_printf("Pour %d coups\n", env->total_cost);
	return (1);
}
