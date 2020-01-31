/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:42:48 by flhember          #+#    #+#             */
/*   Updated: 2020/01/31 18:24:07 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static void	ft_reboot_for_oter(t_lst **lst)
{
	int		i;

	i = 0;
	(*lst)->nb_road = 0;
	while (i < (*lst)->nb_room)
	{
		(*lst)->tab[i]->road = 0;
		(*lst)->tab[i]->dist = 0;
		i++;
	}
}

static int	find_end(t_lst **lst, t_data *env)
{
	size_t	i;

	i = 0;
	while (i < env->nb_room)
	{
		if ((*lst)->tab[i]->end == 1)
		{
			env->end = i;
			return (0);
		}
		i++;
	}
	if (i >= env->nb_room)
		return (-1);
	return (-1);
}

static int	find_start(t_lst **lst, t_data *env)
{
	size_t	i;

	i = 0;
	while (i < env->nb_room)
	{
		if ((*lst)->tab[i]->start == 1)
		{
			env->start = i;
			return (0);
		}
		i++;
	}
	if (i >= env->nb_room)
		return (-1);
	return (-1);
}

void		verif_if_one_pipe(t_lst **lst, t_data *env)
{
	int		i;
	int		j;
	t_room	*tmp;

	i = 0;
	j = 0;
	tmp = (*lst)->tab[env->end];
	while (tmp)
	{
		if (tmp->pos != env->end)
			i++;
		if (tmp->pos == env->start)
			j++;
		tmp = tmp->next;		
	}
	if (i == 1 && j == 1)
		env->nb_con = 1;
}

int			find_nb_pos(t_lst **lst, t_data *env)
{
	int		e;
	int		s;

	e = 0;
	s = 0;
	if ((find_start(lst, env) == -1) || (find_end(lst, env) == -1))
		return (-1);
	if ((e = ft_lstsize_room(&(*lst)->tab[env->end])) == 0)
		return (-1);
	if ((s = ft_lstsize_room(&(*lst)->tab[env->start])) == 0)
		return (-1);
	if (e <= s)
		env->nb_pos = e;
	else
		env->nb_pos = s;
	if (env->nb_pos == 1)
		verif_if_one_pipe(lst, env);
	return (0);
}

int			algo_main(t_lst **lst, t_data *env)
{
	(*lst)->nb_room = env->nb_room;
	if ((*lst)->nb_room == 2 || env->nb_con == 1)
	{
		(*lst)->nb_road = 1;
		if (stock_start_end(lst, env) == -1)
			return (-1);
		return (0);
	}
	creat_road(lst, env);
	if (best_road(lst, env) == -1)
		return (-1);
	if ((*lst)->nb_best_move < (int)env->nb_ants)// && (int)env->nb_ants > 1)
	{
		ft_reboot_for_oter(lst);
		if (other_road(lst, env) == -1)
			return (-1);
	}
//	if (ants_treat(lst, env) == -1)
//		return (-1);
//	print_res(env);
	return (0);
}
