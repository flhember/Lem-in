/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_rep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:20:19 by flhember          #+#    #+#             */
/*   Updated: 2020/01/20 18:02:01 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		treat_better(int limit, t_data *env, int diff)
{
	int *tab;
	int i;
	t_road *cpy;
	int total;
	total = 0;
	i = 0;
	if (!(tab = ft_memalloc(sizeof(int) * limit)))
		return (-1);
	while (i < limit)
	{
		printf("chemin num %d\n", env->road[i + diff]->nb_road);
		cpy = env->road[i + diff];
		tab[i] = (env->nb_ants / limit) + cpy->nb_cost;
		total += tab[i];
		i++;
	}
	free(tab);
	total = total / limit;
	return (total);
}

void 	sort_env(t_data *env)
{
	t_road *cpy;
	int i;

	i = 0;
	if (env->nb_road_f <= 1)
		return ;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->nb_cost > env->road[i + 1]->nb_cost)
		{
			cpy = env->road[i];
			env->road[i] = env->road[i + 1];
			env->road[i + 1] = cpy;
			i = 0;
		}
		else
			i++;
	}
	i = 0;
	while (i < env->nb_road_f)
	{	
		ft_printf("Cost road [%d] -> %d coups\n", i, env->road[i]->nb_cost);
		i++;
	}
}

int		nb_road(t_data *env)
{
	int		i;
	int		cmp;

	i = 0;
	cmp = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->name)
			cmp++;
		i++;
	}
	ft_printf("NB ROAD FINAL = %d | %d\n",cmp, env->nb_road_f);
	return (cmp);
}

int		ants_treat(t_lst **lst, t_data *env)
{
	(*lst)->nb_road--;
	int limit;
	int i;
	int total_cost;
	int cmp;
	//t_road *cpy;
	i = 0;
	cmp = 0;
	limit = 1;
	//while (i < (*lst)->nb_road)
	//{
	//	cpy = env->road[i];
	//	if (cpy->nb_cost <= mid)
	//		limit++;
	//	i++;
	//}
	(*lst)->nb_road = nb_road(env);
	printf("\n\n NB ROAD = %d\n\n", (*lst)->nb_road);
	total_cost = treat_better(limit, env, env->nb_road_f - (*lst)->nb_road);
		ft_printf("total_cost = %d | limit = %d | nb_road = %d\n\n", total_cost, limit, (*lst)->nb_road);
	while (limit < (*lst)->nb_road)
	{
		ft_printf("total_cost = %d | limit = %d | nb_road = %d\n", total_cost, limit, (*lst)->nb_road);
		limit++;
		cmp = total_cost;
		total_cost = treat_better(limit, env, env->nb_road_f - (*lst)->nb_road);
		if (total_cost > cmp)
			total_cost = cmp;
	}
	if (limit > (*lst)->nb_road)
	{
		ft_printf("ca va pas etre possible mon pote, on fait pas de la magie ici\n");
		return (-1);
	}
	ft_printf("\ntotal_cost = %d | limit = %d | nb_road = %d\n", total_cost, limit, (*lst)->nb_road);
	/*
	i = 0;
	if (!(tab =ft_memalloc(sizeof(int) * limit)))
		return (-1);
	while (i < limit)
	{
		cpy = env->road[i];
		tab[i] = (env->nb_ants / limit) + cpy->nb_cost;
		total_cost += tab[i];
		i++;
	}
	total_cost = total_cost / limit;
	i*/
	ft_printf("\n\n____________________________________________\n\n");
	ft_printf("Taille tableau = [ %d ]\n", limit);
	i = 0;
	//while (i < limit)
	//{
	//	ft_printf("Tab[%d] = %d\n", i, tab[i]);
	//	i++;
	//}
	ft_printf("Nombres de coups en passant par %d chemins = %d\n\n", limit, total_cost);
	sort_env(env);
	return (1);
}
