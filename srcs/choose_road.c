/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_road.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:02:17 by chcoutur          #+#    #+#             */
/*   Updated: 2020/01/31 19:15:06 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void	del_queue(t_data *env, int to_del)
{
	t_fail *tmp;
	int i;

	i = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->state == -1)
		{
			tmp = env->road[i]->f_road->next;
			while (tmp)
			{
				ft_printf("ID a delete = %d id actuel = %d\n", to_del, tmp->id);
				if (tmp->id == to_del)
				{
					ft_printf("On tej id %d\n", tmp->id);
					tmp->id = -1;
				}
				tmp = tmp->next;
			}
			ft_putchar('\n');
			env->road[i]->f_road = tmp;
		}
		i++;
	}
}

int		get_id_max(t_data *env)
{
	int max;
	int i;

	i = 0;
	max = i;
	while (env->road[i])
	{
		if (env->road[max]->col < env->road[i]->col)
			max = i;
		i++;
	}
	return (max);
}

int		choose_road(t_data *env)
{
	int id_max;
	int i;

	t_fail *tmp;
	i = 0;
	id_max = get_id_max(env);
	ft_printf("ID chemin col max = %d\n",id_max);
	//if (env->nb_ants < env->road[id_max]->size)
	//{
		ft_printf("fourmis plus petite que le chemin\n");
	//	del_queue(env, id_max);
	//}
//	else
		ft_printf("Fourmis PAS plus petite\n");
	ft_printf("Suppression chemin %d par -1\n", id_max);
	ft_printf("i %d | total road %d\n", i, env->nb_road_f);
	while (i < env->nb_road_f)
	{
		ft_printf("Chemin %d [%s] size = %d:\n", i, env->road[i]->next->name, env->road[i]->size);
		tmp = env->road[i]->f_road;
		while (tmp)
		{
			ft_printf("%d ", tmp->id);
			tmp = tmp->next;
		}
		ft_putchar('\n');
		i++;
	}
	return (1);
}
