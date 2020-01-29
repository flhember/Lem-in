/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_road.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:10:53 by chcoutur          #+#    #+#             */
/*   Updated: 2020/01/29 18:46:58 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void print_road_f(t_data *env)
{
	t_road *tmp;
	int i;

	i = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->state == -1)
		{
			tmp = env->road[i]->next;
			while (tmp && tmp->next != NULL && env->road[i]->state == -1)
			{
				ft_printf("%s", tmp->name);
				if (tmp->next != NULL)
				{
					ft_printf(" ->");
					tmp = tmp->next;
				}
			}
			ft_printf("%20s%d", "| size = ", env->road[i]->size);
			ft_printf("\n");
		}
		i++;
	}
}

int solve_cross(t_data *env)
{
	int i;
	int j;
	int col;

	t_road *nex;
	t_road *act;
	i = 0;
	j = 0;
	col = 0;
	nex = NULL;
	act = NULL;
	while (i < env->nb_road_f)
	{
		act = env->road[i]->next;
		while (act != NULL && act->next != NULL)
		{
			if (i == j)
				j++;
			nex = env->road[j]->next;
			while (nex != NULL && nex->next != NULL)
			{
			//	ft_printf("comparaison %s | %s\n", act->name, nex->name);
				if (act->index == nex->index)
				{
					//ft_printf("\t\tcolission entre %s et %s au chemin %d et %d\n", act->name, nex->name, i, j);
					env->road[i]->state = -1;
					env->road[j]->state = -1;
					col++;
				}
			//	if (nex->next != NULL)
					nex = nex->next;
			}
			j = + 1;
			//if (act->next != NULL)
				act = act->next;
		}
		j = 0;
		i++;
	}
	ft_printf("%d collision\n", col);
	i = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->state == -1)
		{
			ft_printf("_____________________");
			ft_printf("\nChemin [%d] -> KO\n", i);
			ft_printf("_____________________\n\n");
		}
		else
			ft_printf("Chemin [%d] -> OK\n", i);
		i++;
	}
	print_road_f(env);
	return (1);
}


int sort_road(t_data *env)
{
	int i;
	t_road *tmp;

	i = 0;
	tmp = NULL;
	env->nb_road_f--;
	ft_printf("_____________________________\n\n\n\n\n");
	ft_printf("nb_road = %d\n", env->nb_road_f);
	if (env->nb_road_f == 1)
		return (1);
	while (i < env->nb_road_f - 1)
	{
		env->road[i]->state = 0;
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
	
	i = 0;
	while (i < env->nb_road_f)
	{
		//ft_printf("size road %d  = %d\n", i, env->road[i]->size);
		i++;
	}
	solve_cross(env);
	return (1);
}
