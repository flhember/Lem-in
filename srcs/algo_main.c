/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:42:48 by flhember          #+#    #+#             */
/*   Updated: 2019/12/10 17:15:49 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int			find_end(t_lst **lst, t_data *env)
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

int			find_start(t_lst **lst, t_data *env)
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

int			find_nb_pos(t_lst **lst, t_data *env)
{
	int		e;
	int		s;

	e = 0;
	s = 0;
	if ((find_start(lst, env) == -1) || (find_end(lst, env) == -1))
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
	(*lst)->nb_room = env->nb_room;
	if ((find_nb_pos(lst, env)) == -1)
		return (-1);
	if (best_road(lst, env) == -1)
		return (-1);
//	if (env->nb_pos > 1 || (int)env->nb_ants > (*lst)->nb_best_move)
//	{
//		printf("nb ants = %lu, nb->move = %d\n",env->nb_ants, (*lst)->nb_best_move);
//		other_road(lst, env);
//	}
	return (0);
}
