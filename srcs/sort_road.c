/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_road.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:10:53 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/06 18:45:35 by flhember         ###   ########.fr       */
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
			ft_printf("%20s%d\n\n", "| size = ", env->road[i]->size);
			ft_printf("\n");
		}
		i++;
	}
}

int		link_fail(t_data *env, int i, int j)
{
	t_fail *road;
	t_fail *tmp;

	tmp = env->road[i]->f_road;
//	ft_printf("Colission chemin %d et %d\n", i, j);
	if (!(road = ft_memalloc(sizeof(t_fail))))
		return (-1);
	road->id = j;
//	road->next = NULL;
	while (tmp->next)
	{
		ft_printf("ID de %d = %d\n", i, tmp->id);
		tmp = tmp->next;
	}
	tmp->next = road;
	
	return (1);
}

void	mark_fail(t_data *env, int i, int j)
{
	if (env->road[i]->f_road == NULL)
	{
		if (!(env->road[i]->f_road = ft_memalloc(sizeof(t_fail))))
			return ;
		env->road[i]->f_road->id = 0;
	}
	if (env->road[j]->f_road == NULL)
	{
		if (!(env->road[j]->f_road = ft_memalloc(sizeof(t_fail))))
			return ;
		env->road[j]->f_road->id = 0;
	}
	link_fail(env, i, j);
	link_fail(env, j, i);
	env->road[i]->state = -1;
	env->road[j]->state = -1;
	env->road[i]->col++;
	env->road[j]->col++;
}

int solve_cross(t_data *env)
{
	int i;
	int j;
	int col_f;
	int col;

	t_road *nex;
	t_road *act;
	i = 0;
	j = 1;
	col_f = 0;
	col = 0;
	while (i < env->nb_road_f - 1)
	{
		act = env->road[i]->next;
		while (act->next)
		{
			while (j < env->nb_road_f)
			{
				nex = env->road[j]->next;
				while (nex->next)
				{
	//				ft_printf("%s avec %s | chemin %d et %d\n", act->name, nex->name, i, j);
					if (act->index == nex->index && env->road[j]->col == 0)
						mark_fail(env, i, j);
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
	
	
	
//	print_road_f(env);
	return (1);
}


int sort_road(t_data *env)
{
	int i;

	t_road *tmp;
	t_fail *fail;
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
	
	i = 0;
	solve_cross(env);
	i = 0;
	while (i < env->nb_road_f)
	{
		tmp = env->road[i];
		if (tmp->state == -1)
		{
			fail = tmp->f_road->next;
			ft_printf("_____________________");
			ft_printf("\nChemin [%d] -> KO pour %d collisions\n", i, env->road[i]->col);
			ft_printf("Avec chemins :");
			while (fail)
			{
				ft_printf("%d ", fail->id);
				fail = fail->next;
			}
			ft_printf("\n_____________________\n\n");
		}
		else
			ft_printf("Chemin [%d] -> OK\n", i);
		i++;
	}
	choose_road(env);
	return (1);
}