/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_rep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:20:19 by flhember          #+#    #+#             */
/*   Updated: 2020/02/10 16:05:40 by flhember         ###   ########.fr       */
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
int		treat_better(t_data *env, int limit, int id)
{
	int i;
	int total;
	int nb;
	total = 0;
	i = 0;
	nb = 0;
	while (i < env->road_sol[id + 1][0] && i < limit)
	{
//		ft_printf("avec %d\n", env->road_sol[id][i]);
		total = total + ((env->nb_ants / limit) + env->road[env->road_sol[id][i]]->size);
	//	env->road[i]->nb_ant = total; // non juste pour test
		i++;
	}
	total = total / limit;
	return (total);
}
int		ants_treat(t_data *env, int id)
{
	int i;
	int limit;
	int total_cost;
	int tmp;
	i = 0;
	limit = 1;
	env->total_road = 0;
	total_cost = treat_better(env, limit, id);
//	ft_printf("total_cost = %d | limit = %d | nb_road = %d\n", total_cost, limit, env->road_sol[id + 1][0]);
	while (limit < env->road_sol[id + 1][0])
	{
		limit++;
		tmp = total_cost;
		total_cost = treat_better(env, limit, id);
//		ft_printf("->total_cost = %d | limit = %d | nb_road = %d\n", total_cost, limit, env->road_sol[id + 1][0]);
		if (total_cost >= tmp)
		{
			i++;
			total_cost = tmp;
		}
	}
	limit -= i;
	i = 0;
	ft_printf("Chemins a utiliser = \n");
	while (i < limit)
	{
		ft_printf("Chemin [%d] -> %d room\n", env->road_sol[id][i], env->road[env->road_sol[id][i]]->size);
		env->road[i]->nb_ant = env->road[env->road_sol[id][i]]->size;
		i++;
	}
	env->road_sol[id + 1][1] = total_cost;
	env->road_sol[id + 1][0] = limit;
	ft_printf("[[[\tPour %d coups\t]]]\n", env->road_sol[id + 1][1]);
	return (1);
}
