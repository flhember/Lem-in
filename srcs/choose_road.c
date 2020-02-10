/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_road.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:02:17 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/10 14:55:02 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>


int check_fail(t_data *env, int id)
{
	int i;
	t_fail *fail;

	i = 0;
	while (i < id)
	{
		fail = env->road[i]->f_road;
		while (fail)
		{
			if (fail->id == id)
			{
//				ft_printf("Fail : [%d] avec [%d]\n", fail->id, id);
				return (0);
			}
			fail = fail->next;
		}
		i++;
	}
	return (1);
}

int check_fail_state(t_data *env, int id, int state)
{
	int i;
	t_fail *fail;

	i = 0;
	while (i < id)
	{
		if (env->road[i]->state == state)
		{
			fail = env->road[i]->f_road;
			while (fail)
			{
				if (fail->id == id)
				{
//				ft_printf("Fail : [%d] avec [%d]\n", fail->id, id);
					return (0);
				}
				fail = fail->next;
			}
		}
		i++;
	}
	return (1);
}

int		get_ok(t_data *env)
{
	int i;
	int safe;

	i = 0;
	safe = 0;
	while (i < env->nb_road_f)
	{
		if (check_fail(env, i) == 1)
		{
			//ft_printf("Chemin %d est OK\n", i);
			env->road[i]->state = 1;
			safe++;
		}
		else
			env->road[i]->state = -1;
		i++;
	}
	return (safe);
}

int check_road_sol(int id, t_data *env, int size)
{
	int i;

	size++;
	i = 0;
	while (i < env->road_sol[1][0])
	{
		if (env->road_sol[0][i] == id) 
			return (-1);
		i++;
	}
	return (1);
}

int reset_state(t_data *env, int size)
{
	int i;
	int j;
	int state;

	i = 0;
	j = 0;
	state = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->state == 1)
		{
			if ((check_road_sol(i, env, size) == -1)/*i == env->road_sol[j]*/ && env->road[i]->col != 0)
			{
				j++;
				env->road[i]->state = -2;
			}
		}
		else if (env->road[i]->state == 1 || env->road[i]->state == -1)
			state++;
		i++;
	}
	return (state);
}

int	new_tab(int *tab, t_data *env)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->state == 1)
		{
			tab[j] = i;
			j++;
		}
		else if (env->road[i]->state == -1)
		{
			if (check_fail_state(env, i, env->road[i]->state) == 1)
			{
				tab[j] = i;
				j++;
			}
		}
		i++;
	}
	return (j);
}


int		choose_road(t_data *env)
{
	int i;
	int j;
	int ok;
	int tmp_size;
//	int *tab;
	int size_tab;

//	ok = get_ok(env);
	ok = 0;
	tmp_size = 0;
	if (!(env->road_sol = (int**)ft_memalloc(sizeof(int) * 4)))
		return (-1);
	if (!(env->road_sol[0] = (int*)ft_memalloc(sizeof(int) * get_ok(env))))
		return (-1);
	if (!(env->road_sol[1] = (int*)ft_memalloc(sizeof(int) * 1)))
		return (-1);
	env->road_sol[1][0] = get_ok(env);
	//ft_printf("env->road_sol[1][0] = %d\n", env->road_sol[1][0]);
	if (!(env->road_sol[3] = (int*)ft_memalloc(sizeof(int) * 1)))
		return (-1);
	i = 0;
	j = 0;
//	ok = env->nb_road_f;
	while (i < env->nb_road_f)
	{
//		ft_printf("state de %d = %d\n", i, env->road[i]->state);
		if (env->road[i]->state == 1)
		{
			env->road_sol[0][j] = i;
			j++;
		}
		i++;
	}

	/******************
	
	 ********************/
	i = 0;

	while (i < env->road_sol[1][0])
	{
		ft_printf("Chemin OK = [%d]\n", env->road_sol[0][i]);
		i++;
	}
	
	/******************
	
	 ********************/
	ft_printf("\n");
	env->nb_road_f = j;
	ants_treat(env, 0);
//free(env->road_sol);
	tmp_size = env->nb_road_f;
	env->nb_road_f = ok;
	size_tab = reset_state(env, tmp_size);
/*	ft_printf("%d chemins OK\n", size_tab);
	if (!(tab = ft_memalloc(sizeof(int) * size_tab)))
		return (-1);
	size_tab = new_tab(tab, env);
	if (!(env->road_sol = ft_memalloc(sizeof(int) * size_tab)))
		return (-1);
	env->nb_road_f = size_tab;
	env->road_sol = tab;
	ants_treat(env);
*/	
	return (1);
}
