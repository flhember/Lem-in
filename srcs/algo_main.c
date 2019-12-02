/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:42:48 by flhember          #+#    #+#             */
/*   Updated: 2019/12/02 14:57:33 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		print_file(t_file **file, t_lst **lst)
{
	t_file *tmp;

	tmp = *file;
	printf("\n");
	while (tmp)
	{
		printf("[%d - %s] -> ", tmp->dist, (*lst)->tab[tmp->value]->name);
		tmp = tmp->next;
	}
	printf("NULL\n");
}

int			find_end(t_lst **lst, t_data *env)
{
	size_t	i;

	i = 0;
	while (i < env->nb_room)
	{
		if ((*lst)->tab[i]->end == 1)
			return (i);
		i++;
	}
	return (-1);
}

int			pars_pipe(t_lst **lst, t_room *tmp, int i, size_t j)
{
	while (tmp)
	{
		if (tmp->pos == (*lst)->tab[i]->pos)
		{
			if ((*lst)->tab[j]->start == 0)
				(*lst)->tab[j]->road = (*lst)->nb_road;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int			good_road_bis(t_data *env, t_lst **lst, int ds, int i, size_t j, t_room *tmp)
{
	while (ds >= 0)
	{
		printf("\n %s -> %d ", (*lst)->tab[i]->name, ds);
		ds--;
		j = 0;
		while (j < env->nb_room)
		{
			if ((*lst)->tab[j]->dist == ds && (*lst)->tab[j]->road == 0)
			{
				tmp = (*lst)->tab[j];
				if ((pars_pipe(lst, tmp, i, j)))
				{
					i = j;
					j = env->nb_room + 2;
				}
			}
			j++;
			if (j == env->nb_room && ds == (*lst)->tab[env->end]->dist - 1)
			{
				ft_printf("c'est casse pour le chemin %d\n", (*lst)->nb_road);
				return (-1);
			}
		}
	}
	return (0);
}

int			good_road(t_lst **lst, t_data *env)
{
	int		i;
	int		ds;

	while ((*lst)->nb_road < env->nb_pos)
	{
		i = env->end;
		ds = (*lst)->tab[i]->dist;
		printf("\nLa end %s - %d\n", (*lst)->tab[i]->name, ds);
		if ((good_road_bis(env, lst, ds, i, 0, NULL)) == -1)
			(*lst)->tab[env->end]->dist++;
		else
			(*lst)->nb_road++;
		if ((*lst)->tab[env->end]->dist > (int)env->nb_room)
			break;
	}

	return (0);
}

int			find_start(t_lst **lst, t_data *env, t_file **file)
{
	size_t	i;

	i = 0;
	while (i < env->nb_room)
	{
		if ((*lst)->tab[i]->start == 1)
		{
			env->start = i;
			break ;
		}
		i++;
	}
	if (i >= env->nb_room)
		return (-1);
	if ((fill_file(file, lst, i)) == -1)
		return (-1);
	del_first_file(file);
	(*lst)->tab[i]->dist = 0;
	(*lst)->tab[i]->status = 2;
	return (0);
}

int			find_nb_pos(t_lst **lst, t_data *env, t_file **file)
{
	int		e;
	int		s;

	e = 0;
	s = 0;
	printf("find nb pos\n");
	if ((find_start(lst, env, file)) == -1)
	{
		free_file(file);
		return (-1);
	}
	if (((env->end = find_end(lst, env)) == -1))
		return (-1);
	e = ft_lstsize_room(&(*lst)->tab[env->end]);
	s = ft_lstsize_room(&(*lst)->tab[env->start]);
	if (e <= s)
		env->nb_pos = e;
	else
		env->nb_pos = s;
	return (0);
}

int			algo_main(t_lst **lst, t_data *env)
{
	t_file	*file;

	if (!(file = (t_file*)ft_memalloc(sizeof(t_file))))
		return (-1);
	if ((find_nb_pos(lst, env, &file)) == -1)
		return (-1);
	printf("chemins possible %d\n", env->nb_pos);
	bfs(&file, lst);
	good_road(lst, env);
	//print_file(&file, lst);
	free_file(&file);
	return (0);
}
