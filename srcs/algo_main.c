/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:42:48 by flhember          #+#    #+#             */
/*   Updated: 2019/11/29 14:31:13 by flhember         ###   ########.fr       */
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


void	good_road_bis(t_data *env, t_lst **lst, int ds, int i, size_t j, t_room *tmp)
{
	while (ds >= 0)
	{
		printf("\n %s -> %d ", (*lst)->tab[i]->name, ds);
		ds--;
		j = 0;
		while (j < env->nb_room)
		{
			if ((*lst)->tab[j]->dist == ds)
			{
				tmp = (*lst)->tab[j];
				while (tmp)
				{
					if (tmp->pos == (*lst)->tab[i]->pos)
					{
						i = j;
						j = env->nb_room + 2;
					}
					tmp = tmp->next;
				}
			}
			j++;
		}
	}
}

int			good_road(t_lst **lst, t_data *env)
{
	int		i;
	size_t	j;
	int		ds;
	t_room 	*tmp;

	j = 0;
	tmp = NULL;
	i = env->end;
	ds = (*lst)->tab[i]->dist;
	printf("\n %s - %d", (*lst)->tab[i]->name, ds);
	good_road_bis(env, lst, ds, i, j, tmp);
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
